<%'ASP文件接收程序
dim file,obj,fso
file = Trim(Request("file"))
If file = "" Then Response.Write "上传错误文件名未指定": Response.End
Set obj = Server.CreateObject("Adodb.Stream")
With obj
.Type = 1
.Mode = 3
.Open
.Write Request.BinaryRead(Request.TotalBytes)
.Position = 0
.SaveToFile Server.Mappath(file), 2
.Close
End With
Set obj = Nothing
Set fso = CreateObject("Scripting.FileSystemObject")
If fso.FileExists(Server.Mappath(file)) Then
Response.Write "上传成功"
Else
Response.Write "上传失败"
End If
Set fso = Nothing
%>