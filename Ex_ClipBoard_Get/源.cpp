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

//标识需要导出的函数
extern  "C" __declspec(dllexport) char* ClipBoard_Get();

//标识需要导出的函数
extern "C" __declspec(dllexport)  char* ClipBoard_Get_A();

extern "C" __declspec(dllexport) void file_c(char* mess, char* path);

static char* Message_ClipBoard;

//获取需要的文本值
 char* ClipBoard_Get_Old()
{
	char* url, * pData;
	size_t length;
	//打开剪切板
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

//获取剪切板中的文本
 char* ClipBoard_Get_A() {
	//打开剪切板
	if (OpenClipboard(NULL)) {
		//判断格式是否是我们所需要
		if (IsClipboardFormatAvailable(CF_TEXT)) {
			HANDLE hClip;
			char* pBuf;

			//读取数据
			hClip = GetClipboardData(CF_TEXT);
			pBuf = (char*)GlobalLock(hClip);
			GlobalUnlock(hClip);
			//关闭剪切板
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
	 //FILE* fp = fopen("1.txt", mess); //这一行代表创建txt文件
	 //fprintf(fp, "abc\n"); //这一行代表写入内容
 }

//返回固定位置中的值
 char* ClipBoard_Get() {
	 std::fstream myfile;
	 myfile.open("Message.txt", std::ios::out | std::ios::in);
	 //提取内容到Message_ClipBoard;
	 myfile >> Message_ClipBoard;
	 myfile.close();
	return Message_ClipBoard;
}

//不间断循环获取剪切板内容
 void whileW(int final,char* path) {
	int i = 0;
	//当最终循环次数为0时代表循环不间断
	if (final == 0) {
		//循环不间断
		while (true) {
			//ClipBoard_Get_A();
			char* pBuf = ClipBoard_Get_A();
			if (Message_ClipBoard != pBuf)
			{
				file_c(pBuf, path);
				Message_ClipBoard = pBuf;
			}
			//睡眠线程1秒
			Sleep(1000);
		}
	}
	else {
		//循环指定次数
		while (i < final) {
			i++;
			//ClipBoard_Get_A();
			file_c(ClipBoard_Get_A(), path);
		}
	}
}

//第一次执行dll文档时调用，用以初始化数据//final为循环次数
bool First(int final,char* path) {
	//异步调用函数whileW
	//auto Func = std::async(whileW,final);
	whileW(final, path);
	return false;
	//EmptyClipboard();//清空剪切板
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