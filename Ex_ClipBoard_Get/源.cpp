#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <thread>
#include <future>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS

extern "C" __declspec(dllexport) bool First(int final, char* path);

//��ʶ��Ҫ�����ĺ���
extern  "C" __declspec(dllexport) char* ClipBoard_Get();

//��ʶ��Ҫ�����ĺ���
extern "C" __declspec(dllexport)  char* ClipBoard_Get_A();

extern "C" __declspec(dllexport) void file_c(char* mess, char* path);

static char* Message_ClipBoard;

//��ȡ��Ҫ���ı�ֵ
 char* ClipBoard_Get_Old()
{
	char* url, * pData;
	size_t length;
	//�򿪼��а�
	OpenClipboard(NULL);
	HANDLE hData = GetClipboardData(CF_TEXT);
	assert(hData != NULL);
	length = GlobalSize(hData);
	url = (char*)malloc(length + 1);
	pData = (char*)GlobalLock(hData);
	//strcpy(url, pData);
	url = pData;
	GlobalUnlock(hData);
	CloseClipboard();
	url[length] = 0;
	printf("%s\n", url);
	return url;
}

//��ȡ���а��е��ı�
 char* ClipBoard_Get_A() {
	//�򿪼��а�
	if (OpenClipboard(NULL)) {
		//�жϸ�ʽ�Ƿ�����������Ҫ
		if (IsClipboardFormatAvailable(CF_TEXT)) {
			HANDLE hClip;
			char* pBuf;

			//��ȡ����
			hClip = GetClipboardData(CF_TEXT);
			pBuf = (char*)GlobalLock(hClip);
			GlobalUnlock(hClip);
			//�رռ��а�
			CloseClipboard();
			return pBuf;
		}
	}
	char* c = Message_ClipBoard;
	return c;
}

 void file_c(char* mess,char* path) {
	 std::ofstream myfile;
	 myfile.open(path);
	 myfile << mess << "\r\n";
	 myfile.close();
	 //FILE* fp = fopen("1.txt", mess); //��һ�д�����txt�ļ�
	 //fprintf(fp, "abc\n"); //��һ�д���д������
 }

//���ع̶�λ���е�ֵ
 char* ClipBoard_Get() {
	 std::fstream myfile;
	 myfile.open("Message.txt", std::ios::out | std::ios::in);
	 //��ȡ���ݵ�Message_ClipBoard;
	 myfile >> Message_ClipBoard;
	 myfile.close();
	return Message_ClipBoard;
}

//�����ѭ����ȡ���а�����
 void whileW(int final,char* path) {
	int i = 0;
	//������ѭ������Ϊ0ʱ����ѭ�������
	if (final == 0) {
		//ѭ�������
		while (true) {
			//ClipBoard_Get_A();
			char* pBuf = ClipBoard_Get_A();
			if (Message_ClipBoard != pBuf)
			{
				file_c(pBuf, path);
				Message_ClipBoard = pBuf;
			}
			//˯���߳�1��
			Sleep(1000);
		}
	}
	else {
		//ѭ��ָ������
		while (i < final) {
			i++;
			//ClipBoard_Get_A();
			file_c(ClipBoard_Get_A(), path);
		}
	}
}

//��һ��ִ��dll�ĵ�ʱ���ã����Գ�ʼ������//finalΪѭ������
bool First(int final,char* path) {
	//�첽���ú���whileW
	//auto Func = std::async(whileW,final);
	whileW(final, path);
	return false;
	//EmptyClipboard();//��ռ��а�
}

int main() {
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	std::cout << ClipBoard_Get_A();
	return 0;
}