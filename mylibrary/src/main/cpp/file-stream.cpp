//
// Created by binbinHan on 1/25/22.
//
#include <jni.h>
#include <vector>
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
 *
 * 读写文件 ：
　　读写文件分为文本文件和二进制文件的读取，对于文本文件的读取比较简单，用插入器和析取器就可以了；而对于二进制的读取就要复杂些

 * 1.文本文件的读写
　　文本文件的读写很简单：用插入器(<<)向文件输出；用析取器(>>)从文件输入。假设file1是以输入方式打开，file2以输出打开。示例如下：
　　file2<<"I Love You";//向文件写入字符串"I Love You"
　　int i;
　　file1>>i;//从文件输入一个整数值。

 * 文本文件写入文件
 * 在 C++ 编程中，我们使用流插入运算符（ << ）向文件写入信息，就像使用该运算符输出信息到屏幕上一样。唯一不同的是，在这里您使用的是 ofstream 或 fstream 对象，而不是 cout 对象。
 *
 * 文本文件读取文件
 * 在 C++ 编程中，我们使用流提取运算符（ >> ）从文件读取信息，就像使用该运算符从键盘输入信息一样。唯一不同的是，在这里您使用的是 ifstream 或 fstream 对象，而不是 cin 对象。
 *
 * 1.fstream提供了三个类，用来实现c++对文件的操作。（文件的创建、读、写）：
     ifstream ：从已有的文件读入
     ofstream ： 向文件写内容
     fstream ： 打开文件供读写

    2.文件打开模式：
      ios::in             只读
      ios::out            只写
      ios::app            从文件末尾开始写，防止丢失文件中原来就有的内容
      ios::binary         二进制模式
      ios::nocreate       打开一个文件时，如果文件不存在，不创建文件
      ios::noreplace      打开一个文件时，如果文件不存在，创建该文件
      ios::trunc          打开一个文件，然后清空内容
      ios::ate            打开一个文件时，将位置移动到文件尾

    3.文件指针位置的用法：
      ios::beg   文件头
      ios::end   文件尾
      ios::cur   当前位置

    例子：
    file.seekg(0,ios::beg);   //让文件指针定位到文件开头
    file.seekg(0,ios::end);   //让文件指针定位到文件末尾
    file.seekg(10,ios::cur);   //让文件指针从当前位置向文件末方向移动10个字节
    file.seekg(-10,ios::cur);   //让文件指针从当前位置向文件开始方向移动10个字节
    file.seekg(10,ios::beg);   //让文件指针定位到离文件开头10个字节的位置
    注意：移动的单位是字节，而不是行。

 * 2.二进制文件的读写
　　①put()
　　put()函数向流写入一个字符，其原型是ofstream &put(char ch)，使用也比较简单，如file1.put('c');就是向流写一个字符'c'。

　　②get()
　　get()函数比较灵活，有3种常用的重载形式：
　　一种就是和put()对应的形式：ifstream &get(char &ch);功能是从流中读取一个字符，结果保存在引用ch中，如果到文件尾，返回空字符。如file2.get(x);表示从文件中读取一个字符，并把读取的字符保存在x中。
　　另一种重载形式的原型是： int get();这种形式是从流中返回一个字符，如果到达文件尾，返回EOF，如x=file2.get();和上例功能是一样的。
　　还有一种形式的原型是：ifstream &get(char *buf,int num,char delim='/n')；这种形式把字符读入由 buf 指向的数组，直到读入了 num 个字符或遇到了由 delim 指定的字符，
    如果没使用 delim 这个参数，将使用缺省值换行符'/n'。例如：
　　file2.get(str1,127,'A');//从文件中读取字符到字符串str1，当遇到字符'A'或读取了127个字符时终止。

　　③读写数据块
　　要读写二进制数据块，使用成员函数read()和write()成员函数，它们原型如下：
　　read(unsigned char *buf,int num);
　　write(const unsigned char *buf,int num);
　　read()从文件中读取 num 个字符到 buf 指向的缓存中，如果在还未读入 num 个字符时就到了文件尾，可以用成员函数 int gcount();来取得实际读取的字符数；
   而 write() 从buf 指向的缓存写 num 个字符到文件中，值得注意的是缓存的类型是 unsigned char *，有时可能需要类型转换。
　　例：
　　unsigned char str1[]="I Love You";
　　int n[5];
　　ifstream in("xxx.xxx");
　　ofstream out("yyy.yyy");
　　out.write(str1,strlen(str1));//把字符串str1全部写到yyy.yyy中
　　in.read((unsigned char*)n,sizeof(n));//从xxx.xxx中读取指定个整数，注意类型转换
　　in.close();
   out.close();
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

    //第一种读取文件内容(infile.getline() 按行读取; 以标识"\n"为界)
    char buffer[1024];
    //底层，如果到达文件尾返回非0值，否则返回0
    while (!infile.eof()) {
        infile.getline(buffer, 1024); //如果一行超过1024个字符（utf-8编码格式下一个汉字暂用三个字符）；此处会进入死循环
        LOGE("循环获取内容,size = %d  content= %s", strlen(buffer), buffer);
        for (int i = 0; i < strlen(buffer); i++) {
            LOGE("打印每个字符内容, content= %c", buffer[i]);
            LOGE("打印每个字符内容对应的int值, content= %d", buffer[i]);
        }
        str.append(buffer);
    }
    infile.close();
    LOGE("从文件中获取的内容，%s", str.c_str()); // 因为"%s"要求后面的对象的首地址

//    //第二种读取文件内容
//    //底层，如果到达文件尾返回非0值，否则返回0
//    string current;
//    while (getline(infile, current)) {
//        LOGE("循环获取内容,size = %d  content= %s", strlen(current.c_str()), current.c_str());
//        str.append(current); //此处可以换成 vector<string> content;  content.push_back(str);
//    }
//    infile.close();
//    LOGE("从文件中获取的内容，%s", str.c_str()); // 因为"%s"要求后面的对象的首地址

//    //第三种读取文件内容
//    vector<string> content;
//    while (infile >> str) {
//        content.push_back(str);
//    }
//    infile.close();
//    LOGE("从文件中获取的内容vector长度，%d", content.size());
//    for (auto &i : content) {
//        LOGE("从文件中获取的内容，%s", i.c_str()); // 因为"%s"要求后面的对象的首地址
//    }
}

/**
 * 往文件内写内容
 * @param content
 */
void writeContentToFile(string content) {
    //string 转 char 下面两种方式都可以
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
    outfile << data; //或者直接使用 outfile << content
    outfile << "结束写入数据\n";
    outfile.close();
}

