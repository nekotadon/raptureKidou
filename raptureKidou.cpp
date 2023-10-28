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

	// Shiftが押されているか
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		shift = 1;
	}

	char Path[MAX_PATH + 1];

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH))
	{
		// ファイルパス
		char drive[MAX_PATH + 1], dir[MAX_PATH + 1], fname[MAX_PATH + 1], ext[MAX_PATH + 1];

		// パスを分解
		_splitpath(Path, drive, dir, fname, ext);

		// フォルダパス取得
		string folder(drive);
		folder += dir;

		// ファイル存在確認用
		struct stat st;

		int check = 0;
		if (shift == 1)
		{
			// shiftが押されている場合

			// rapture.iniのパス
			string rapture_path;
			rapture_path = folder + "rapture.ini";

			// ファイル読み込み
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
				// 改行削除
				if (strlen(str) > 0)
				{
					if (str[strlen(str) - 1] == '\n')
					{
						str[strlen(str) - 1] = '\0';
					}
				}

				// 1行読み取り
				line = str;

				if (line.length() > savestr.length())
				{
					string savepath = line.substr(0, savestr.length());

					// 保存先指定行か
					if (savepath == savestr)
					{
						// 保存フォルダ取得
						savepath = line.substr(savestr.length());

						// 末尾\削除
						if (savepath.length() > 0)
						{
							if (savepath.substr(savepath.length() - 1) == "\\")
							{
								savepath = savepath.substr(0, savepath.length() - 1);
							}
						}

						// 保存フォルダがある場合
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
			// ファイルを閉じる
			fclose(fp);

			if (check == 1)
			{
				// フォルダが存在する場合
				char *cmd = new char[folder.size() + 1];
				strcpy(cmd, folder.c_str());

				// フォルダを開く
				if ((INT_PTR)ShellExecute(NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL) > 32)
				{
					return 0;
				}
			}
			return 1;
		}
		else
		{
			// shiftが押されていない場合

			// raptureのパス
			string rapture_path;
			rapture_path = folder + "rapture.exe";

			// ファイルが存在するか
			stat(rapture_path.c_str(), &st);

			if (S_ISREG(st.st_mode))
			{
				// ファイルが存在する場合
				PROCESS_INFORMATION pi = {0};
				STARTUPINFO si = {sizeof(STARTUPINFO)};

				char *cmd = new char[rapture_path.size() + 1];
				strcpy(cmd, rapture_path.c_str());

				// ファイル実行
				if (CreateProcess(NULL, cmd, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
				{
					return 0;
				}
			}
		}
	}

	return 1;
}
