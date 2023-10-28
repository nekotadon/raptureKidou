#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <shellapi.h>

#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m)&S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m)&S_IFMT) == S_IFDIR)
#endif

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int shift = 0;

	// Shift��������Ă��邩
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		shift = 1;
	}

	char Path[MAX_PATH + 1];

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH))
	{
		// �t�@�C���p�X
		char drive[MAX_PATH + 1], dir[MAX_PATH + 1], fname[MAX_PATH + 1], ext[MAX_PATH + 1];

		// �p�X�𕪉�
		_splitpath(Path, drive, dir, fname, ext);

		// �t�H���_�p�X�擾
		string folder(drive);
		folder += dir;

		// �t�@�C�����݊m�F�p
		struct stat st;

		int check = 0;
		if (shift == 1)
		{
			// shift��������Ă���ꍇ

			// rapture.ini�̃p�X
			string rapture_path;
			rapture_path = folder + "rapture.ini";

			// �t�@�C���ǂݍ���
			FILE *fp = fopen(rapture_path.c_str(), "r");
			char str[1024];

			string line;
			string savestr = "AutoSaveDirName=";

			if (fp == NULL)
			{
				return 1;
			}
			while (fgets(str, 1024, fp) != NULL)
			{
				// ���s�폜
				if (strlen(str) > 0)
				{
					if (str[strlen(str) - 1] == '\n')
					{
						str[strlen(str) - 1] = '\0';
					}
				}

				// 1�s�ǂݎ��
				line = str;

				if (line.length() > savestr.length())
				{
					string savepath = line.substr(0, savestr.length());

					// �ۑ���w��s��
					if (savepath == savestr)
					{
						// �ۑ��t�H���_�擾
						savepath = line.substr(savestr.length());

						// ����\�폜
						if (savepath.length() > 0)
						{
							if (savepath.substr(savepath.length() - 1) == "\\")
							{
								savepath = savepath.substr(0, savepath.length() - 1);
							}
						}

						// �ۑ��t�H���_������ꍇ
						stat(savepath.c_str(), &st);

						if (S_ISDIR(st.st_mode))
						{
							check = 1;
							folder = savepath;
							break;
						}
					}
				}
			}
			// �t�@�C�������
			fclose(fp);

			if (check == 1)
			{
				// �t�H���_�����݂���ꍇ
				char *cmd = new char[folder.size() + 1];
				strcpy(cmd, folder.c_str());

				// �t�H���_���J��
				if ((INT_PTR)ShellExecute(NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL) > 32)
				{
					return 0;
				}
			}
			return 1;
		}
		else
		{
			// shift��������Ă��Ȃ��ꍇ

			// rapture�̃p�X
			string rapture_path;
			rapture_path = folder + "rapture.exe";

			// �t�@�C�������݂��邩
			stat(rapture_path.c_str(), &st);

			if (S_ISREG(st.st_mode))
			{
				// �t�@�C�������݂���ꍇ
				PROCESS_INFORMATION pi = {0};
				STARTUPINFO si = {sizeof(STARTUPINFO)};

				char *cmd = new char[rapture_path.size() + 1];
				strcpy(cmd, rapture_path.c_str());

				// �t�@�C�����s
				if (CreateProcess(NULL, cmd, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
				{
					return 0;
				}
			}
		}
	}

	return 1;
}
