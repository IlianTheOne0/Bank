namespace Database.Loop;

using InfrastructureServer.Models.Config;

using Microsoft.Extensions.DependencyInjection;
using Confluent.Kafka;
using Confluent.Kafka.Admin;
using System.Text;

internal partial class DatabaseLoop
{
    private static async Task<(CancellationTokenSource, IConsumer<string, byte[]>)> LoadKafka(AppConfig Config)
    {
        CancellationTokenSource cts = new CancellationTokenSource();
        IConsumer<string, byte[]> consumer = null!;

        try
        {
            ConsumerConfig consumerConfig = new ConsumerConfig
            {
                BootstrapServers = Config.Kafka.BootstrapServers,
                GroupId = Config.Kafka.GroupId,
                AutoOffsetReset = AutoOffsetReset.Earliest,
                EnableAutoCommit = true,
                ApiVersionRequestTimeoutMs = 5000,
                SocketTimeoutMs = 5000
            };

            using (IAdminClient adminClient = new AdminClientBuilder(consumerConfig).Build())
            {
                try
                {
                    var topics = Config.Kafka.Topics.Values.Select
                    (
                        topic => new TopicSpecification
                        {
                            Name = topic,
                            NumPartitions = 1,
                            ReplicationFactor = 1
                        }
                    );

                    await adminClient.CreateTopicsAsync(topics);
                }
                catch (CreateTopicsException E) when (E.Results[0].Error.Code == ErrorCode.TopicAlreadyExists) { Console.WriteLine($"Topic with name {E.Results[0].Topic} already exists!"); }
                catch (Exception E) { Console.WriteLine($"Topic creation error: {E.Message}"); }
            }

            consumer = new ConsumerBuilder<string, byte[]>(consumerConfig).Build();
            consumer.Subscribe(new[] { "database-commands" });

            Console.WriteLine($"Subscribed to {Config.Kafka.Topics.Values}. Waiting for messages... Press Ctrl+C to stop.");

            Console.CancelKeyPress += (sender, e) => { e.Cancel = true; cts.Cancel(); };

            return (cts, consumer);
        }
        catch (Exception E)
        {
            Console.WriteLine($"Fatal error: {E.Message}\n{E.StackTrace}");
            consumer?.Dispose();
            cts.Dispose();
            throw;
        }
    }

    private static async Task ProcessTheMessages(AppConfig Config, CancellationTokenSource Cts, IConsumer<string, byte[]> Consumer, ServiceProvider ServiceProvider)
    {
        while (!Cts.IsCancellationRequested)
        {
            try
            {
                var cr = Consumer.Consume(Cts.Token);
                var json = Encoding.UTF8.GetString(cr.Message.Value);

                Console.WriteLine($"\nReceived from {cr.Topic}: {json}");

                await HandleMessage(Config, cr.Topic, json, ServiceProvider, Cts.Token);
            }
            catch (OperationCanceledException) { break; }
            catch (ConsumeException E) { Console.WriteLine($"Consume error: {E.Error.Reason}"); }
            catch (Exception E) { Console.WriteLine($"Processing error: {E.Message}"); }
        }

        Consumer.Close();
    }
}