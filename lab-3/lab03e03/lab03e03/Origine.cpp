#define UNICODE
#define _UNICODE
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <tchar.h>

#define L 500

#define TYPE_FILE 1
#define TYPE_DIR 2
#define TYPE_DOT 3


static void TraverseAndCreate(LPTSTR, LPTSTR);
static int FileType(LPWIN32_FIND_DATA);

int _tmain(int argc, LPTSTR argv[]) {

	if (argc != 3) {
		_tprintf(_T("Wrong number of parameters\n"));
		return 1;
	}

	TCHAR tmpPath[L], DestPathName[L];
	

	//	****RELATIVE PATH****
	//GetCurrentDirectory(L, tmpPath);
	//_stprintf(DestPathName, _T("%s\\%s"), tmpPath, argv[2]);

	//TraverseAndCreate(argv[1], DestPathName);
	
	//	****ABSOLUTE PATH****
	TraverseAndCreate(argv[1], argv[2]);

}

static void TraverseAndCreate(LPTSTR SourcePathName, LPTSTR DestPathName) {
	WIN32_FIND_DATA FindData;
	HANDLE SearchHandle;
	HANDLE hIn, hOut;
	int Ftype;
	int l;
	DWORD nW, nR;
	TCHAR newPath[L], twoLine[L];
	TCHAR c;
	LARGE_INTEGER size;

	_tprintf( _T("Create dir: %s\n"), DestPathName);

	CreateDirectory(DestPathName, NULL);
	SetCurrentDirectory(SourcePathName);
	SearchHandle = FindFirstFile(_T("*"), &FindData);
	
	do {
		//_ftprintf(stdout, _T("File: %s\n"), FindData.cFileName);
		Ftype = FileType(&FindData);

		if (DestPathName[_tcslen(DestPathName) - 1] == _T('\\')) {
			_stprintf(newPath, _T("%s%s"), DestPathName, FindData.cFileName);
		}
		else {
			_stprintf(newPath, _T("%s\\%s"), DestPathName, FindData.cFileName); 
		}

		if (Ftype == TYPE_FILE) {
			//_ftprintf(stdout, _T("File: %s is a file\n"), FindData.cFileName);
			//copy file from src to dst dir
			//CopyFile(FindData.cFileName, newPath, FALSE);
			hIn = CreateFile(FindData.cFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			hOut = CreateFile(newPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hIn == INVALID_HANDLE_VALUE || hOut == INVALID_HANDLE_VALUE) {
				_tprintf(_T("error\n"));
				exit(EXIT_FAILURE);
			}
			GetFileSizeEx(hIn, &size);
			_stprintf(twoLine, _T("%s\n%d\n"), FindData.cFileName, size);
			WriteFile(hOut, twoLine, _tcslen(twoLine)*sizeof(TCHAR), &nW, NULL);

			while (ReadFile(hIn, &c, sizeof(TCHAR), &nR, NULL) && nR > 0) {
				// Convert single char into a record (file line) string
					WriteFile(hOut, &c, sizeof(TCHAR), &nW, NULL);
			}
			
			CloseHandle(hIn);
			CloseHandle(hOut);
		}
		else if (Ftype == TYPE_DIR) {
			//_ftprintf(stdout, _T("File: %s is a dir\n"), FindData.cFileName);
			TraverseAndCreate(FindData.cFileName, newPath);
			SetCurrentDirectory(_T(".."));
			
		}
		
	} while (FindNextFile(SearchHandle, &FindData));

	FindClose(SearchHandle);
	
	return;
}

static int FileType(LPWIN32_FIND_DATA pFileData) {
	int type = TYPE_FILE;
	// bitwise AND between "The file attributes of a file" and "The handle that identifies a directory"
	if (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		if (lstrcmp(_T(".."), pFileData->cFileName) == 0 || lstrcmp(_T("."), pFileData->cFileName) == 0)
			type = TYPE_DOT;
		else type = TYPE_DIR;
	}

	return type;
}

