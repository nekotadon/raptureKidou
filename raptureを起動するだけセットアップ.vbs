'rapture.exe�Ɠ����t�H���_�ɓ���Ď��s����

'vbs�t�@�C���̂���t�H���_���擾
Set objFSO = WScript.CreateObject("Scripting.FileSystemObject")
folder = objFSO.GetParentFolderName(WScript.ScriptFullName)

'vbs�t�@�C���̂���t�H���_����ƃt�H���_��
Set objWSell = WScript.CreateObject("WScript.Shell")
objWSell.CurrentDirectory = folder

'�t�@�C���p�X
lnk = folder & "\rapture.lnk"
exe = folder & "\rapture���N�����邾��.exe"
raptureexe = folder & "\rapture.exe"

'�V���[�g�J�b�g�̍쐬
Set shortcut = objWSell.CreateShortcut(lnk)

With shortcut
	'�����N��̃t�@�C����
	.TargetPath = exe
	'��ƃt�H���_
	.WorkingDirectory= folder
	'�V���[�g�J�b�g�̃A�C�R��
	.IconLocation = raptureexe & ", 0"
	'�ۑ�
    .Save
End With
