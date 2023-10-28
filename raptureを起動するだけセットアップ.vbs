'rapture.exeと同じフォルダに入れて実行する

'vbsファイルのあるフォルダを取得
Set objFSO = WScript.CreateObject("Scripting.FileSystemObject")
folder = objFSO.GetParentFolderName(WScript.ScriptFullName)

'vbsファイルのあるフォルダを作業フォルダに
Set objWSell = WScript.CreateObject("WScript.Shell")
objWSell.CurrentDirectory = folder

'ファイルパス
lnk = folder & "\rapture.lnk"
exe = folder & "\raptureを起動するだけ.exe"
raptureexe = folder & "\rapture.exe"

'ショートカットの作成
Set shortcut = objWSell.CreateShortcut(lnk)

With shortcut
	'リンク先のファイル名
	.TargetPath = exe
	'作業フォルダ
	.WorkingDirectory= folder
	'ショートカットのアイコン
	.IconLocation = raptureexe & ", 0"
	'保存
    .Save
End With
