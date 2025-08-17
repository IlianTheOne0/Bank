namespace ApplicationClient.Responses.Database;

using ApplicationClient.Responses.Base;

public class ResponsesDatabase : ResponsesBase
{
    public object Data { get; set; }

    public static ResponsesDatabase Ok(object Data = null, string Message = "")
        => new ResponsesDatabase
        {
            Success = true,
            Data = Data,
            Message = Message
        };

    public static ResponsesDatabase Fail(string Error, string Message = "", object Data = null)
        => new ResponsesDatabase
        {
            Success = false,
            Error = Error,
            Message = Message,
            Data = Data
        };
}

public class ResponsesDatabase<TAnswer> : ResponsesDatabase
{
    public new TAnswer Data
    {
        get => (TAnswer)base.Data;
        set => base.Data = value;
    }
}