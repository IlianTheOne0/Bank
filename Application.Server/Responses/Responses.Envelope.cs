namespace ApplicationServer.Responses.Envelope;

using ApplicationServer.Responses.Base;
using ApplicationServer.Responses.Database;

public class ResponsesEnvelope : ResponsesBase
{
    public string ResponseTopic { get; set; }
    public ResponsesDatabase? Response { get; set; }
}