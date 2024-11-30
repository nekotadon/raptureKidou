//rapture.exeと同じフォルダに入れて実行する

//jsファイルのあるフォルダを取得
var objFSO = new ActiveXObject("Scripting.FileSystemObject");
var folder = objFSO.GetParentFolderName(WScript.ScriptFullName);

//jsファイルのあるフォルダを作業フォルダに
var objShell = new ActiveXObject("WScript.Shell");
objShell.CurrentDirectory = folder;

//ファイルパス
lnk = folder + "\\rapture.lnk";
exe = folder + "\\raptureを起動するだけ.exe";
raptureexe = folder + "\\rapture.exe";

// ショートカットの作成
var shortcut = objShell.CreateShortcut(lnk);

shortcut.TargetPath = exe; // リンク先のファイル名
shortcut.WorkingDirectory = folder; // 作業フォルダ
shortcut.IconLocation = raptureexe + ", 0"; // ショートカットのアイコン

shortcut.Save(); // 保存