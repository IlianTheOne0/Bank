namespace ApplicationClient.Responses.Envelope;

using ApplicationClient.Responses.Database;

public class ResponsesEnvelope
{
    public Guid CorrelationId { get; set; }
    public ResponsesDatabase Response { get; set; }
}