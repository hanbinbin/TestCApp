//
// Created by binbinHan on 1/25/22.
//
#include <jni.h>
#include <string>
#include "file-stream.h"
#include "log.h"
#include "common.h"

using namespace std;

/**
 * 注释
 *
 * 1.打开文件：
 * 在从文件读取信息或者向文件写入信息之前，必须先打开文件。ofstream 和 fstream 对象都可以用来打开文件进行写操作，如果只需要打开文件进行读操作，则使用 ifstream 对象。
 * 下面是 open() 函数的标准语法，open() 函数是 fstream、ifstream 和 ofstream 对象的一个成员。
 * void open(const char *filename, ios::openmode mode);
 * 在这里，open() 成员函数的第一参数指定要打开的文件的名称和位置，第二个参数定义文件被打开的模式

 *    模式标志	    描述
 *    ios::app	    追加模式。所有写入都追加到文件末尾。
 *    ios::ate	    文件打开后定位到文件末尾。
 *    ios::in	    打开文件用于读取。
 *    ios::out	    打开文件用于写入。
 *    ios::trunc	如果该文件已经存在，其内容将在打开文件之前被截断，即把文件长度设为 0。
 *
 * 您可以把以上两种或两种以上的模式结合使用。例如，如果您想要以写入模式打开文件，并希望截断文件，以防文件已存在，那么您可以使用下面的语法：
 * ofstream outfile;
 * outfile.open("file.dat", ios::out | ios::trunc );
 *
 * 类似地，您如果想要打开一个文件用于读写，可以使用下面的语法：
 * ifstream  afile;
 * afile.open("file.dat", ios::out | ios::in );
 *
 * 2.关闭文件
 * 当 C++ 程序终止时，它会自动关闭刷新所有流，释放所有分配的内存，并关闭所有打开的文件。但程序员应该养成一个好习惯，在程序终止前关闭所有打开的文件。
 * 下面是 close() 函数的标准语法，close() 函数是 fstream、ifstream 和 ofstream 对象的一个成员。
 * void close();
 *
 * 3.写入文件
 * 在 C++ 编程中，我们使用流插入运算符（ << ）向文件写入信息，就像使用该运算符输出信息到屏幕上一样。唯一不同的是，在这里您使用的是 ofstream 或 fstream 对象，而不是 cout 对象。
 *
 * 4.读取文件
 * 在 C++ 编程中，我们使用流提取运算符（ >> ）从文件读取信息，就像使用该运算符从键盘输入信息一样。唯一不同的是，在这里您使用的是 ifstream 或 fstream 对象，而不是 cin 对象。
 */


/**
 * 从文件获取内容
 * @return
 */
void getContentFromFile() {
    string str;
    ifstream infile;
    infile.open("/storage/emulated/0/Android/data/cn.huolala.testcapp/cache/test.txt");
    if (!infile.is_open()) {
        return;
    }
    char buffer[1024];
    //底层，如果到达文件尾返回非0值，否则返回0
    while (!infile.eof()) {
        infile.getline(buffer, 100);
        LOGE("循环获取内容,size = %d  content= %s", strlen(buffer), buffer);
        str.append(buffer);
    }
    infile.close();
    LOGE("从文件中获取的内容，%s", str.c_str()); // 因为"%s"要求后面的对象的首地址
}

/**
 * 往文件内写内容
 * @param content
 */
void writeContentToFile(string content) {
    //string 转 char
    char *data;
//    data = const_cast<char *>(content.c_str());
    data = (char *) content.c_str();
    ofstream outfile;
    outfile.open(
            "/storage/emulated/0/Android/data/cn.huolala.testcapp/cache/test.txt");
    if (!outfile.is_open()) {
        return;
    }
    outfile << "开始写入数据\n";
    outfile << data;
    outfile << "结束写入数据\n";
    outfile.close();
}

