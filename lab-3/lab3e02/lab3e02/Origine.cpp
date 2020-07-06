//		*******	VERSION A	*********
//#define UNICODE
//#define _UNICODE
//
//#define _CRT_SECURE_NO_WARNINGS
//
//
//#include <Windows.h>
//#include <tchar.h>
//#include <stdio.h>
//
//#define L (30 + 1)
//
//typedef struct mys {
//	DWORD id;      // also INT
//	DWORD rn;      // also LONG
//	TCHAR n[L];
//	TCHAR s[L];
//	DWORD mark;    // also INT
//}mys_t;
//
//int _tmain(int argc, LPTSTR argv[]) {
//	if (argc != 2) {
//		printf("Wrong number of parameters.\n");
//
//	}
//	DWORD nR;
//	mys_t myse;
//	//TCHAR buf[L];
//	TCHAR val;
//	DWORD intVal;
//	LARGE_INTEGER FilePos;
//	PLARGE_INTEGER lpFilePos;
//	lpFilePos = (PLARGE_INTEGER)malloc(1 * sizeof(LARGE_INTEGER));
//
//	HANDLE hIn;
//	hIn = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
//		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if (hIn == INVALID_HANDLE_VALUE) {
//		fprintf(stderr, "Cannot open input file. Error: %x\n", GetLastError());
//		Sleep(2000);
//		return 2;
//	}
//
//	do {
//		_ftscanf(stdin, _T("%c"), &val);
//
//		if (val == _T('R')) {
//			_ftscanf(stdin, _T("%d"), &intVal);
//			FilePos.QuadPart = intVal * sizeof(mys_t);
//			SetFilePointerEx(hIn, FilePos, lpFilePos, FILE_BEGIN);
//			ReadFile(hIn, &myse, sizeof(mys_t), &nR, NULL);
//			_tprintf(_T("-> %d %ld %s %s %d <-\n"),
//				myse.id, myse.rn, myse.n, myse.s, myse.mark);
//		}
//		else if (val == _T('W')) {
//			_ftscanf(stdin, _T("%d"), &intVal);
//			_tprintf(_T("Data: "));
//			_ftscanf(stdin, _T("%d%ld%s%s%d"), &myse.id, &myse.rn, myse.n, myse.s, &myse.mark);
//			FilePos.QuadPart = intVal * sizeof(mys_t);
//			SetFilePointerEx(hIn, FilePos, lpFilePos, FILE_BEGIN);
//			WriteFile(hIn, &myse, sizeof(struct mys), &nR, NULL);
//		}
//	} while (val != _T('E'));
//
//}


////		*******	VERSION B	*********
//#define UNICODE
//#define _UNICODE
//
//#define _CRT_SECURE_NO_WARNINGS
//
//
//#include <Windows.h>
//#include <tchar.h>
//#include <stdio.h>
//
//#define L (30 + 1)
//
//typedef struct mys {
//	DWORD id;      // also INT
//	DWORD rn;      // also LONG
//	TCHAR n[L];
//	TCHAR s[L];
//	DWORD mark;    // also INT
//}mys_t;
//
//int _tmain(int argc, LPTSTR argv[]) {
//	if (argc != 2) {
//		printf("Wrong number of parameters.\n");
//
//	}
//	DWORD nR;
//	mys_t myse;
//	TCHAR val;
//	DWORD intVal;
//	LARGE_INTEGER FilePos;
//	OVERLAPPED ov = {0, 0, 0, 0, NULL};
//
//	HANDLE hIn;
//	hIn = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
//		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if (hIn == INVALID_HANDLE_VALUE) {
//		fprintf(stderr, "Cannot open input file. Error: %x\n", GetLastError());
//		Sleep(2000);
//		return 2;
//	}
//
//	do {
//		_ftscanf(stdin, _T("%c"), &val);
//
//		if (val == _T('R')) {
//			_ftscanf(stdin, _T("%d"), &intVal);
//			FilePos.QuadPart = intVal * sizeof(mys_t);
//			ov.Offset = FilePos.LowPart;
//			ov.OffsetHigh = FilePos.HighPart;
//			ReadFile(hIn, &myse, sizeof(mys_t), &nR, &ov);
//			_tprintf(_T("-> %d %ld %s %s %d <-\n"),
//				myse.id, myse.rn, myse.n, myse.s, myse.mark);
//		}
//		else if (val == _T('W')) {
//			_ftscanf(stdin, _T("%d"), &intVal);
//			_tprintf(_T("Data: "));
//			_ftscanf(stdin, _T("%d%ld%s%s%d"), &myse.id, &myse.rn, myse.n, myse.s, &myse.mark);
//			FilePos.QuadPart = intVal * sizeof(mys_t);
//			ov.Offset = FilePos.LowPart;
//			ov.OffsetHigh = FilePos.HighPart;
//			WriteFile(hIn, &myse, sizeof(struct mys), &nR, &ov);
//		}
//	} while (val != _T('E'));
//
//}

//		*******	VERSION C	*********
#define UNICODE
#define _UNICODE

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#define L (30 + 1)

typedef struct mys {
	DWORD id;      // also INT
	DWORD rn;      // also LONG
	TCHAR n[L];
	TCHAR s[L];
	DWORD mark;    // also INT
}mys_t;

int _tmain(int argc, LPTSTR argv[]) {
	if (argc != 2) {
		printf("Wrong number of parameters.\n");

	}
	DWORD nR;
	mys_t myse;
	TCHAR val;
	DWORD intVal;
	LARGE_INTEGER FilePos, fileReserved;
	OVERLAPPED ov = { 0, 0, 0, 0, NULL };

	HANDLE hIn;
	hIn = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hIn == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open input file. Error: %x\n", GetLastError());
		Sleep(2000);
		return 2;
	}

	do {
		_ftscanf(stdin, _T("%c"), &val);

		if (val == _T('R')) {
			_ftscanf(stdin, _T("%d"), &intVal);

			FilePos.QuadPart = intVal * sizeof(mys_t);
			fileReserved.QuadPart = 1 * sizeof(mys_t);

			ov.Offset = FilePos.LowPart;
			ov.OffsetHigh = FilePos.HighPart;
			ov.hEvent = (HANDLE)0;

			LockFileEx(hIn, LOCKFILE_EXCLUSIVE_LOCK, 0, fileReserved.LowPart, fileReserved.HighPart, &ov);

			ReadFile(hIn, &myse, sizeof(mys_t), &nR, &ov);

			UnlockFileEx(hIn, 0, fileReserved.LowPart, fileReserved.HighPart, &ov);
			_tprintf(_T("-> %d %ld %s %s %d <-\n"),
				myse.id, myse.rn, myse.n, myse.s, myse.mark);
		}
		else if (val == _T('W')) {
			_ftscanf(stdin, _T("%d"), &intVal);
			_tprintf(_T("Data: "));
			_ftscanf(stdin, _T("%d%ld%s%s%d"), &myse.id, &myse.rn, myse.n, myse.s, &myse.mark);

			FilePos.QuadPart = intVal * sizeof(mys_t);
			fileReserved.QuadPart = 1 * sizeof(mys_t);
			ov.Offset = FilePos.LowPart;
			ov.OffsetHigh = FilePos.HighPart;
			ov.hEvent = (HANDLE)0;

			LockFileEx(hIn, LOCKFILE_EXCLUSIVE_LOCK, 0, fileReserved.LowPart, fileReserved.HighPart, &ov);
			WriteFile(hIn, &myse, sizeof(struct mys), &nR, &ov);
			UnlockFileEx(hIn, 0, fileReserved.LowPart, fileReserved.HighPart, &ov);
		}
	} while (val != _T('E'));

}