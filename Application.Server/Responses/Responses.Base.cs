namespace ApplicationServer.Responses.Base;

public abstract class ResponsesBase
{
    public Guid CorrelationId { get; set; }
    public bool Success { get; set; }
    public string Message { get; set; }
    public string Error { get; set; }
}