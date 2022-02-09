//
// Created by binbinHan on 1/25/22.
//

#ifndef TESTCAPP_FILE_STREAM_H
#define TESTCAPP_FILE_STREAM_H

#include <iostream>
#include <fstream>

using namespace std;

//从文件读取流和向文件写入流。这就需要用到 C++ 中另一个标准库 fstream
//ofstream	该数据类型表示输出文件流，用于创建文件并向文件写入信息。
//ifstream	该数据类型表示输入文件流，用于从文件读取信息。
//fstream	该数据类型通常表示文件流，且同时具有 ofstream 和 ifstream 两种功能，这意味着它可以创建文件，向文件写入信息，从文件读取信息。
//要在 C++ 中进行文件处理，必须在 C++ 源代码文件中包含头文件 <iostream> 和 <fstream>
/**
 * 从文件中获取内容，转为string
 * @return
 */
void getContentFromFile();

/**
 * 往文件内写入内容 content
 * @param content
 */
void writeContentToFile(string content);

#endif //TESTCAPP_FILE_STREAM_H
