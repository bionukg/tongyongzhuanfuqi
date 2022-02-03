#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<direct.h>
#include <io.h>
#include<Windows.h>
//#define test
typedef struct foldr
{
    
};
int gp = 0, mode = 0;
int slp = 100;
_finddata_t fileinfo1, fileinfo2;
intptr_t fhd1, fhd2;
#define buffer_size 1024
char ctrl_c[0x1000] = { 0 }, ctrl_v[0x1000] = { 0 }, path_b[0x100] = { 0 }, myself[0x1000] = { 0 };
void crdir(char* path);

FILE* fopenc(const char* _FileName, const char* _Mode);

void str_add(char*str ,const char*add)
{
    int i = 0;
    int j = 0;
    for (j = 0; str[j] != 0; j++);

    for (; add[i]!=0; i++)
    {
        str[j + i] = add[i];
    }
    str[j + i] = 0;
    return;
}
void str_del(char* str, const char* del) 
{
    int i = 0;
    int j = 0;
    for (j = 0; str[j] != 0; j++);

    for (; del[i] != 0; i++)
    {
        str[j - i] = 0;
    }
    str[j - i] = 0;
    return;
}
void str_del_a(char* str)
{
    int i = 0;
sd1:
    if (str[i] != 0)
    {
        i++;
    }
    else
    {
        i--;
        str[i] = 0;
        return;
    }
    goto sd1;
}
void str_add_a(char* str, char a)
{
    int i = 0;
sa1:
    if (str[i] != 0)
    {
        i++;
    }
    else
    {
        str[i] = a;
        i++;
        str[i] = 0;
        return;
    }
    goto sa1;
}
void fcopy(FILE* fc, FILE* fv, unsigned long length)
{
    if (fc == 0 || fv == 0)
    {
        printf("\nerror:copy_file null file pointer\n");
        //system("pause");
        return;
    }
    char* buffer = (char*)malloc(buffer_size);
    unsigned long copyed = length;
    while (length > 0)
    {
        if (length >= buffer_size) {
            fread(buffer, 1, buffer_size, fc);
            fwrite(buffer, 1, buffer_size, fv);
            length -= buffer_size;
        }
        else {
            fread(buffer, 1, length, fc);
            fwrite(buffer, 1, length, fv);
            length = 0;
        }
    }
    free(buffer);
    printf("%ld Bytes copyed\n", copyed);

    return;
}
void thispath(char* this_path,const char* path)
{
    int i = 0;
tp1:
    if (path[i] != 0)
    {
        this_path[i] = path[i];
    }
    else
    {
        this_path[i] = 0;
        goto tp2;
    }
    i++;
    goto tp1;
tp2:
    switch (this_path[i])
    {
    case '\\':
    case '/':
        i++;
        this_path[i] = 0;
        goto tp3;
    default:
        this_path[i] = 0;
        i--;
        break;
    }
    goto tp2;
tp3:
    return;


}
void this_folder(char* folder, char* path)//获得路径中最后一层的名字
{
    int i = 0, j = 0, k = 0;
    while (path[i] != 0)
    {
        i++;
    }

tf0:
    switch (path[i--])
    {

    case '\\':
    case '/':goto tf1;
    default:
        if (i >= 0)
        {
            goto tf0;
        }
        else
        {
            goto tf1;
        }
        break;
    }

tf1:
    j = i;
    while (path[i] != '/' && path[i] != '\\' && i >= 0)
    {
        i--;
    }
    k = i + 1;
    for (int l = 0; k <= j; k++, l++)
    {
        folder[l] = path[k];
    }
    return;
}
int _cdecl fclosea(FILE* stm)
{
    if (stm == 0)
        return -1;
    else
    {
        return fclose(stm);
    }
}
void getpath(char* path)
{
#ifndef test
    for (int i = 0; i < 0x1000; i++)
    {
        scanf("%c", &path[i]);
        switch (path[i])
        {
        case '\n':
            path[i++] = '/';
            path[i++] = '*';
            path[i++] = 0;
            goto path_end;
        default:
            break;
        }
    }
    std::cout << "可能出了些问题。你不是在搞事吧？\t——bionukg\n";
    system("pause");
    exit(250);
path_end:
    return;
#else
    if (gp++ == 0)
    {
        strcpy(path, "C:/Program Files/Genshin Impact bilibili/*");
    }
    else
    {
        strcpy(path, "C:/Genshin Impact miHoYo/*");
    }
    std::cout << path << "\n";
#endif // test
}
void show_fileinfo(struct _finddata_t fileinfo)
{

    printf("\nattrib:\t%#x\n", fileinfo.attrib);
    printf("name:\t%s\n", fileinfo.name);
    printf("size:\t%ld\n", fileinfo.size);
    printf("time_access:\t%lld\n", fileinfo.time_access);
    printf("time_create:\t%lld\n", fileinfo.time_create);
    printf("time_write:\t%lld\n", fileinfo.time_write);
}
bool file_comparer(FILE* fpa, FILE* fpb)
{
  
    if (fpa == 0)
    {
        std::cout << "出了些意外，我决定忽略。\t——bionukg\n";
        
        return 0;
    }
    if (fpb == 0)
    {
        return 0;
    }

    fseek(fpa, 0, SEEK_END);
    fseek(fpb, 0, SEEK_END);
    if (ftell(fpa) != ftell(fpb))
        return 0;
    fseek(fpa, 0, SEEK_SET);
    fseek(fpb, 0, SEEK_SET);
    int* bufa, * bufb;
    bufa = (int*)calloc(0x1000, sizeof(int));
    bufb = (int*)calloc(0x1000, sizeof(int));
    if (bufa == 0 || bufb == 0)
    {
        std::cout << "你内存炸了。我不管了。\t——bionukg\n";
        system("pause");
        exit(250);
        return 0;
    }
    else
    {
        int i1 = 0, i2 = 0;
    next_turn:
        i1 = fread(bufa, sizeof(int), 0x1000, fpa);
        i2 = fread(bufb, sizeof(int), 0x1000, fpb);
        if (i1 != i2)
        {
            return 0;
        }
        else
        {
            for (int i = 0; i < i1; i++)
            {
                if (bufa[i] != bufb[i])
                    return 0;
            }
        }
        if (i1 < 0x1000)
        {
            return 1;
        }
        else
        {
            goto next_turn;
        }
    }
}
//精确到文件
int file_backuper(char* path_c, char* path_v, char* path_b)
{//0未备份，1备份且成功，-1出错
    int r = 0;
    FILE* fpc = 0, * fpv = 0, * fpb = 0;
    if (path_c == 0 || path_v == 0)
    {
        std::cout << "程序炸了。我决定忽略。你可以暂停或者趁机退出。\t——bionukg\n";
        Sleep(slp++);
        r = -1;
        goto ret;
    }
    fpc = fopenc(path_c, "rb");
    if (mode == 1) {
        fpv = fopenc(path_v, "rb");
    }
    else
    {
        goto opfpb;
    }
    if (file_comparer(fpc, fpv))
    {
        r = 0;
        goto ret;
    }
    else
    {
    opfpb:
        fpb = fopenc(path_b, "wb+");
        fseek(fpc, 0, SEEK_END);
        long leng = ftell(fpc);
        fseek(fpc, 0, SEEK_SET);
        std::cout << path_c<<"\n";
        fcopy(fpc, fpb, leng);
        r = 1;
    }

ret:
    fclosea(fpc);
    fclosea(fpv);
    fclosea(fpb);
    return r;
}

int file_checker(char* path_c, char* path_v, char* path_b)
{
    int fhd;
    _finddata_t finfo;
    int fn = 0;
    fhd = _findfirst(path_c, &finfo);
    if (fhd == -1)
    {
        std::cout << "程序炸了。即将退出。\n\n";
        Sleep(1000);
        system("pause");
        exit(250);
    }
    fdn:
    //如果是文件夹，则递归
    if (finfo.attrib == _A_SUBDIR)
    {
        if (strcmp(finfo.name, ".") == 0 || strcmp(finfo.name, "..") == 0)
        {
            fn = _findnext(fhd, &finfo);
            if (fn == -1)
            {
                _findclose(fhd);
                return 1;
            }
            goto fdn;
        }
        else
        {
            str_add(path_b, "/");
            str_add(path_b, finfo.name);
            str_del(path_c, "1");
            str_add(path_c, finfo.name);
            str_add(path_c, "/*");
            str_del(path_v, "1");
            str_add(path_v, finfo.name);
            str_add(path_v, "/*");
            if (mode == 1) 
            {
                fn = _mkdir(path_b);
                if (0 != fn)
                {
                    printf("程序又㕛双叒叕出问题了，早告诉你新建一个文件夹了...\n");
                    printf("这个路径——\n%s\n——被占用了，所以我跳过了它。", path_b);
                    goto backuped;
                }
            }
            printf("checking %s\n",path_c);
            file_checker(path_c, path_v, path_b);
        backuped:
            str_del(path_v, "/*");
            str_del(path_v, finfo.name);
            str_add(path_v, "*");
            str_del(path_c, "/*");
            str_del(path_c, finfo.name);
            str_add(path_c, "*");
            str_del(path_b, finfo.name);
            str_del(path_b, "1");
        }
    }
    //如果是文件，则filebackuper
    else
    {
        str_del(path_c, "1");
        str_add(path_c, finfo.name);
        str_del(path_v, "1");
        str_add(path_v, finfo.name);
        str_add(path_b, "/");
        str_add(path_b, finfo.name);

        printf("checking %s\n", path_c);
        file_backuper(path_c, path_v, path_b);

        str_del(path_b, finfo.name);
        str_del(path_b, "1");
        str_del(path_v, finfo.name);
        str_add(path_v, "*");
        str_del(path_c, finfo.name);
        str_add(path_c, "*");
    }
    fn = _findnext(fhd, &finfo);
    if (fn == -1)
    {
        _findclose(fhd);
        return 0;
    }
    else
    {
        goto fdn;
    }
    return 0;
}
int main(int argc, char** argv)
{
    int i = 0;
    char ans,tem;
    printf("请选择模式：\n1.生成模式\t2.替换模式\n输入序号：");
scans:
    scanf("%c", &ans);
    if (ans != '\n') {
        scanf("%c", &tem);
        if (tem != '\n')
        {
            do {
                scanf("%c", &tem);
            } while (tem != '\n');
            goto resca;
        }
    }
    switch (ans)
    {
    case '1':
        mode = 1;
        goto chosen;
    case '2':
        mode = 2;
        goto chosen;

    case '\n':
        goto resca;
    default:
         while (tem != '\n'){
            scanf("%c", &tem);
        } 

        break;
    }
resca:
    system("cls");
    printf("请“正确地”选择模式：\n1.生成模式\t2.替换模式\n输入序号：");
    goto scans;
chosen:
    thispath(myself, *argv);
    if (mode == 1)
    {
        printf("建议把本程序放到新建文件夹里操作，保证文件夹里只有这个程序。\n不然炸了不管我事。\t——bionukg\n\n");
        



        std::cout << "输入原版路径。原版路径将被替换\n例如：C:/Users/bionukg_v1.0\n";
        getpath(ctrl_v);

        std::cout << "输入新版路径。新版路径将替换原版\n例如：C:/Users/bionukg_v2.0\n";
        getpath(ctrl_c);
        

        this_folder(path_b, ctrl_c);
        int lm = 0;
        for (; myself[lm] != 0; lm++);
        for (int i = 0; path_b[i] != 0; i++)
        {
            myself[lm + i] = path_b[i];
        }

        i = _mkdir(myself);
        if (0 != i)
        {
            printf("\n目录——\n%s\n——已存在！！！把本程序放到新建文件夹里重新操作！！！\n不然炸了真不管我事！！！\t——bionukg\n\n", myself);
            system("pause");
        }


        //std::cout << "Hello World!\n";

        //_mkdir()

        file_checker(ctrl_c, ctrl_v, myself);
        std::cout << "如果一切顺利的话，这个程序的旁边会多出一个文件夹。保存好这个文件夹，以后还有用。\nPS:比如打个压缩包，然后丢进电子邮件当做附件发给你自己。\n";
        std::cout << "\n\n生成模式结束。程序即将关闭。\n\n";
        system("pause");
        return 0;
    }
    /*fhd1 = _findfirst(ctrl_c, &fileinfo1);
    fhd2 = _findfirst(ctrl_v, &fileinfo2);
    std::cout << "\n" << fhd1 << "\n" << fhd2 << "\n";
    if (fhd1 != -1) {
        show_fileinfo(fileinfo1);
    }
    else
    {
        system("pause");
        exit(250);
    }
    if (fhd2 != -1) {
        show_fileinfo(fileinfo2);
    }
    else
    {
        system("pause");
        exit(250);
    }
    while (0 == _findnext(fhd1, &fileinfo1) && 0 == _findnext(fhd2, &fileinfo2))
    {
        show_fileinfo(fileinfo1);
        printf("then\n");
        show_fileinfo(fileinfo2);
    }*/
    else if (mode == 2)
    {
        strcpy(ctrl_c, myself);
        str_add(ctrl_c, "空文件夹");//一个用来占位的空文件夹，如果程序结束还没有自动消失请手动删除。");
        
        std::cout << "是时候把你在生成模式得到的文件夹掏出来了。\n谨记：务必使与本程序同处于一个文件夹的东西有且仅有那个“生成模式的文件夹”，跟生成模式结束时的情况一样。\n";
        printf("\n你现在可以退出。\n");
        std::cout << "好的。现在输入原版路径吧。此程序将根据“生成模式的文件夹”把它不严格地替换成新版。\nPS:“不严格”的意思是，如果原版比新版多了些文件，替换过程并不会删除。据我所知几乎所有程序并不会管相关文件夹多出来的东西。\n";
        getpath(ctrl_v);
        str_del(ctrl_v, "/*");
        str_add(myself, "*");
        int fn = 0;
        fhd1 = _findfirst(myself, &fileinfo1);

    md2refind:
        if (fn == -1)
        {
            printf("请按说明操作。");
            system("pause");
            exit(250);
        }
        if (strcmp(fileinfo1.name, ".") == 0 || strcmp(fileinfo1.name, "..") == 0)
        {
            fn = _findnext(fhd1, &fileinfo1);
            goto md2refind;
        }
        else if(fileinfo1.attrib==_A_SUBDIR)
        {
            str_del(myself, "*");
            str_add(myself, fileinfo1.name);
        }
        else
        {
            goto md2refind;
        }
        gp=_mkdir(ctrl_c);
        str_add(myself, "/*");
        str_add(ctrl_c, "/*");

        file_checker(myself, ctrl_c, ctrl_v);
        str_del(ctrl_c, "/*");
        gp=_rmdir(ctrl_c);
        std::cout << "\n\n替换模式结束。程序即将关闭。\n\n";
        system("pause");
        return 0;
    }
    else
    {
        printf("认真的？好吧，如果你在运行中的程序中见到了这行字，向我反馈这个情况。——bionukg");
        system("pause");
    }
    return 0;
}
void crdir(char* path)
{
    char* this_pth=(char*)malloc(MAX_PATH*sizeof(char));
crd:
    if (0 != _mkdir(path))
    {
        if (errno == ENOENT) {
            _set_errno(0);
            thispath(this_pth, path);
            str_del(this_pth, "1");
            crdir(this_pth);
            goto crd;
        }
        else if(errno == EEXIST)
        {
            goto crd2;
        }
        else
        {
            printf("cridr unexpected\n");
        }
    }
crd2:
    free(this_pth);
    return;
}
FILE* fopenc(const char* _FileName, const char* _Mode)
{
    char* this_pth = (char*)malloc(MAX_PATH* sizeof(char));
    thispath(this_pth, _FileName);
    str_del(this_pth, "1");

    crdir(this_pth);
    free(this_pth);
    return fopen(_FileName, _Mode);
}
