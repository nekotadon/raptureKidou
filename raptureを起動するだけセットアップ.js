//rapture.exe�Ɠ����t�H���_�ɓ���Ď��s����

//js�t�@�C���̂���t�H���_���擾
var objFSO = new ActiveXObject("Scripting.FileSystemObject");
var folder = objFSO.GetParentFolderName(WScript.ScriptFullName);

//js�t�@�C���̂���t�H���_����ƃt�H���_��
var objShell = new ActiveXObject("WScript.Shell");
objShell.CurrentDirectory = folder;

//�t�@�C���p�X
lnk = folder + "\\rapture.lnk";
exe = folder + "\\rapture���N�����邾��.exe";
raptureexe = folder + "\\rapture.exe";

// �V���[�g�J�b�g�̍쐬
var shortcut = objShell.CreateShortcut(lnk);

shortcut.TargetPath = exe; // �����N��̃t�@�C����
shortcut.WorkingDirectory = folder; // ��ƃt�H���_
shortcut.IconLocation = raptureexe + ", 0"; // �V���[�g�J�b�g�̃A�C�R��

shortcut.Save(); // �ۑ�