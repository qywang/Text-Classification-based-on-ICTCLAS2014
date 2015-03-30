// win_cDemo.cpp : 定义控制台应用程序的入口点。
//

#include "../../include/NLPIR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
 using namespace std ;
#ifndef OS_LINUX
#pragma comment(lib, "../lib/NLPIR.lib")
#endif

//Linux
#ifdef OS_LINUX
	#define _stricmp(X,Y) strcasecmp((X),(Y))
	#define _strnicmp(X,Y,Z) strncasecmp((X),(Y),(Z))
	#define strnicmp(X,Y,Z)	strncasecmp((X),(Y),(Z))
	#define _fstat(X,Y)     fstat((X),(Y))
	#define _fileno(X)     fileno((X))
	#define _stat           stat
	#define _getcwd         getcwd
	#define _off_t          off_t
	#define PATH_DELEMETER  "/"
#else
	#pragma warning(disable:4786)
	#define PATH_DELEMETER  "\\"
#endif
//void SplitGBK(const char *sInput);
//void SplitBIG5();
//void SplitUTF8();
//void testNewWord();
struct Keywords_Stat //统计词频
{
	string s;
	int keyword_freq;//词频
	int libnum[11];//属于哪一类
};
Keywords_Stat Keywords[100];
int keyword_num=0;//关键词个数
int word_num=0;//段落总词数
double LIB[11]={0};//关键词在每个词库中出现的总次数

void testWord(int nCode)
{
	//初始化分词组件
	if(!NLPIR_Init("..",nCode))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	char sInputFile[1024]="../test/test.TXT",sResultFile[1024];
	//if (nCode==UTF8_CODE)
	//{
		//strcpy(sInputFile,"../test/test-utf8.TXT");
	//}

	//NLPIR
	const char *sResult=NLPIR_GetFileKeyWords(sInputFile);//提取关键词，存在Result.txt中
	FILE *fp=fopen("Result.txt","wb");
	fprintf(fp,sResult);
	fclose(fp);
	strcpy(sResultFile,sInputFile);
	strcat(sResultFile,"_result1.txt");
	NLPIR_FileProcess(sInputFile,sResultFile);//分词，存在test.TXT_result1.txt中

	ifstream fin1("Result.txt");
	char c[20];
	
	int i=0,j=0;
	string s_key,s2;
    fin1>>s_key;
	cout<<endl<<"关键词:"<<endl;
	const char*s=s_key.c_str();
	while (s[i]!='\0')
	{
		j=0;
		while(s[i]!='#')
		{
			c[j]=s[i];
			j++;i++;
		}
		c[j]='\0';
		Keywords[keyword_num].s=c;
		cout<<Keywords[keyword_num].s<<"  ";
		i++;keyword_num++;
	}
	cout<<keyword_num<<endl;
	fin1.close();
	fin1.clear();
	ifstream fin2(sResultFile);
	string Total_Words[500];
	i=0;j=0;
	cout<<endl<<"分词结果:"<<endl;
	while( fin2 >> s2 ) 
    {  
       s=s2.c_str();
	   if(s[3]!='w'&&s[2]!='w')//去掉标点符号
	   {
			while(s[i]!='/')
			{
				c[j]=s[i];
				j++;i++;
			}
			c[j]='\0';
			Total_Words[word_num]=c;
			
			cout<<Total_Words[word_num]<<"  ";
			j=0;i=0;word_num++;
	   }
    }
	cout<<endl<<"词频统计结果："<<endl;
	fin2.close();
	fin2.clear();
	i=0;j=0;
	for(i=0;i<=keyword_num-1;i++)
	{
		Keywords[i].keyword_freq=0;
		for(j=0;j<=word_num-1;j++)
			if(Keywords[i].s==Total_Words[j])
				Keywords[i].keyword_freq++;
	}
	for(i=0;i<=keyword_num-1;i++)
		cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<" ";
	cout<<endl;

   //fp=fopen("ResultNew.txt","wb");
   
    
	//int totalwordcount=NLPIR_GetParagraphProcessAWordCount(sResultFile);
	//cout<<totalwordcount<<endl;
	//s=s2.c_str();
	/*string word[500];
    i=0;j=0;k=0;
	while (s[i]!='\0')
	{
		j=0;
		while(s[i] & 0x80)
		{
			c[j]=s[i];
			j++;i++;
		}
		c[j]='\0';
		word[k]=c;
		cout<<word[k]<<endl;
		while(!s[i] & 0x80)
		{i++;}
		k++;
	}
	//fin2.close();
	//fin2.clear();*/
	/*for(int i=0; s[i] != '\0'; i++)
    {
        if(!(s[i] & 0x80))
        {   
            printf("this is a char:%c\n",s[i]);
        }
        else //中文编码
        {
            char w[2];//以字符串的形式存储汉字
            w[0] = s[i];
            w[1] = s[i+1];       
            printf("this is a chinese:%2s\n",w);
            i++;
        }
    }*/
  
	//cout<<wcount<<endl;
	
	//sResult=NLPIR_GetFileNewWords(sInputFile);
	//fp=fopen("ResultNew.txt","wb");
	//fprintf(fp,sResult);
	//fclose(fp);

	//NLPIR_NWI_Start();
	//NLPIR_NWI_AddFile(sInputFile);
	//NLPIR_NWI_Complete();
	//const char *pNewWordlist=NLPIR_NWI_GetResult();
	//printf("识别出的新词为：%s\n",pNewWordlist);

	

	//NLPIR_NWI_Result2UserDict();//新词识别结果

	//strcpy(sResultFile,sInputFile);
	//strcat(sResultFile,"_result2.txt");
	//NLPIR_FileProcess(sInputFile,sResultFile);

	NLPIR_Exit();
}

void KW_Topic_Classify()
{
	int i=0,j=0;
	string s_temp1,s_temp2,s_temp3,s_temp4,s_temp5,s_temp6,s_temp7,s_temp8,s_temp9,s_temp10;
    cout<<keyword_num;
	ifstream fin1("词库一-生活.txt");
	ifstream fin2("词库二-医疗保健.txt");
	ifstream fin3("词库三-体育.txt");
	ifstream fin4("词库四-娱乐.txt");
	ifstream fin5("词库五-旅游.txt");
	ifstream fin6("词库六-政治.txt");
	ifstream fin7("词库七-科技.txt");
	ifstream fin8("词库八-军事.txt");
	ifstream fin9("词库九-财经.txt");
	ifstream fin10("词库十-教育文化.txt");
	
	fin1>>s_temp1;fin1.close();fin1.clear();
	fin2>>s_temp2;fin2.close();fin2.clear();
	fin3>>s_temp3;fin3.close();fin3.clear();
	fin4>>s_temp4;fin4.close();fin4.clear();
	fin5>>s_temp5;fin5.close();fin5.clear();
	fin6>>s_temp6;fin6.close();fin6.clear();
	fin7>>s_temp7;fin7.close();fin7.clear();
	fin8>>s_temp8;fin8.close();fin8.clear();
	fin9>>s_temp9;fin9.close();fin9.clear();
	fin10>>s_temp10;fin10.close();fin10.clear();
	cout<<"根据名词词库分类结果如下："<<endl;
	//cout<<endl<<s_temp8<<endl;
	
	for(i=0;i<=keyword_num-1;i++)
	{
		Keywords[i].libnum[0]=1;//词库中没有该词
		if (s_temp1.find(Keywords[i].s)!=string::npos&&s_temp1.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[1]=1;
			Keywords[i].libnum[0]=0;
			LIB[1]=LIB[1]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[1]=0;
		if (s_temp2.find(Keywords[i].s)!=string::npos&&s_temp2.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[2]=1;
			Keywords[i].libnum[0]=0;
			LIB[2]=LIB[2]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[2]=0;
		if (s_temp3.find(Keywords[i].s)!=string::npos&&s_temp3.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[3]=1;
			Keywords[i].libnum[0]=0;
			LIB[3]=LIB[3]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[3]=0;
		if (s_temp4.find(Keywords[i].s)!=string::npos&&s_temp4.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[4]=1;
			Keywords[i].libnum[0]=0;
			LIB[4]=LIB[4]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[4]=0;
		if (s_temp5.find(Keywords[i].s)!=string::npos&&s_temp5.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[5]=1;
			Keywords[i].libnum[0]=0;
			LIB[5]=LIB[5]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[5]=0;
		if (s_temp6.find(Keywords[i].s)!=string::npos&&s_temp6.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[6]=1;
			Keywords[i].libnum[0]=0;
			LIB[6]=LIB[6]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[6]=0;
		if (s_temp7.find(Keywords[i].s)!=string::npos)//&&s_temp7.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[7]=1;
			Keywords[i].libnum[0]=0;
			LIB[7]=LIB[7]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[7]=0;
		if (s_temp8.find(Keywords[i].s)!=string::npos&&s_temp8.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[8]=1;
			Keywords[i].libnum[0]=0;
			//cout<<Keywords[i].s<<":"<<s_temp8.find(Keywords[i].s);
			LIB[8]=LIB[8]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[8]=0;
		if (s_temp9.find(Keywords[i].s)!=string::npos&&s_temp9.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[9]=1;
			Keywords[i].libnum[0]=0;
			LIB[9]=LIB[9]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[9]=0;
		if (s_temp10.find(Keywords[i].s)!=string::npos&&s_temp10.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[10]=1;
			Keywords[i].libnum[0]=0;
			LIB[10]=LIB[10]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[10]=0;
	}
	for(i=0;i<=10;i++)
		cout<<LIB[i]<<"  ";
	for(i=0;i<=keyword_num-1;i++)
	{
		if(Keywords[i].libnum[0]==1)
			cout<<Keywords[i].s<<":词库中无该词！";
		else
		{
			cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<"  :属于词库";
			for(j=0;j<=10;j++)
				if(Keywords[i].libnum[j]==1)
					cout<<j;
		}
		cout<<endl;
	}
}

int NaiveBayes(int doc,int ccount[],int total)
{
	double p1=0,p_temp=0,bayes_temp=0,numerator,denominator;
	int i=0,cl=0;
	double test=pow(2,(double)10);
	cout<<test;
	
	for(i=1;i<=doc;i++)
	{
		numerator=pow(2,LIB[i]);
	    denominator=pow(total+ccount[i-1],(double)keyword_num);
		//cout<<"ccount[i-1]:"<<ccount[i-1];
		cout<<"total+ccount[i-1]:"<<total+ccount[i-1];
		bayes_temp=numerator/denominator;
		cout<<"numerator:"<<numerator<<"/"<<"denominator:"<<denominator<<"="<<bayes_temp;
		p_temp=(double)ccount[i-1]/(double)total;//先验概率
		cout<<"      ccount[i-1]:"<<ccount[i-1]<<"/"<<"total:"<<total<<"="<<p_temp;
		p_temp=p_temp*bayes_temp;
		
		if(p_temp>p1)
		{
			if((doc==2)&&(p_temp/p1<=10))//判断中性情感
				cl=3;
			else
			{
				p1=p_temp;
				cl=i;
			}
		}
		else
			if((doc==2)&&(p1/p_temp<=10))//判断中性情感
				cl=3;
		cout<<"    "<<i<<":"<<p_temp<<endl;
	}
	//cout<<numerator<<"/"<<denominator<<"="<<p1;
	cout<<"段落属于类别："<<cl<<endl;
	return cl;
}

void KW_Emo_Classify()
{
	int i=0,j=0;
	string s_temp1,s_temp2,s_temp3,s_temp4,s_temp5,s_temp6,s_temp7,s_temp8,s_temp9,s_temp10;
	ifstream fin1("一-中文负面评价词语.txt");
	//ifstream fin2("二-中文负面情感词语.txt");
	ifstream fin2("二-中文正面评价词语.txt");
	//ifstream fin4("四-中文正面情感词语.txt");
	//ifstream fin3("三-中性词语.txt");
	
	fin1>>s_temp1;fin1.close();fin1.clear();
	fin2>>s_temp2;fin2.close();fin2.clear();
	//fin3>>s_temp3;fin3.close();fin3.clear();
	cout<<"根据情感词库分类结果如下："<<endl;
    LIB[1]=LIB[2]=LIB[3]=0;
	
	for(i=0;i<=keyword_num-1;i++)
	{
		//Keywords[i].s="、"+Keywords[i].s+"、";
		Keywords[i].libnum[0]=1;//词库中没有该词
		if (s_temp1.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[1]=1;
			Keywords[i].libnum[0]=0;
			LIB[1]++;
		}
		else
			Keywords[i].libnum[1]=0;
		if (s_temp2.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[2]=1;
			Keywords[i].libnum[0]=0;
			LIB[2]++;
		}
		else
			Keywords[i].libnum[2]=0;
		//if (s_temp3.find(Keywords[i].s)!=string::npos)
		//{
			//Keywords[i].libnum[3]=1;
			//Keywords[i].libnum[0]=0;
			//LIB[3]++;
		//}
		//else
			//Keywords[i].libnum[3]=0;
	}
	for(i=0;i<=2;i++)
		cout<<LIB[i]<<"  ";
	for(i=0;i<=keyword_num-1;i++)
	{
		if(Keywords[i].libnum[0]==1)
			cout<<Keywords[i].s<<":词库中无该词！";
		else
		{
			cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<"  :属于词库";
			for(j=0;j<=2;j++)
				if(Keywords[i].libnum[j]==1)
					cout<<j;
		}
		cout<<endl;
	}
}

void KW_Emo_Level_Classify()
{
	int i=0,j=0;
	string s_temp1,s_temp2,s_temp3,s_temp4,s_temp5,s_temp6;

	ifstream fin1("1.极其.txt");
	ifstream fin2("2.很.txt");
	ifstream fin3("3.比较.txt");
	ifstream fin4("4.稍微.txt");
	ifstream fin5("5.欠.txt");
	ifstream fin6("6.过度.txt");
	
	fin1>>s_temp1;fin1.close();fin1.clear();
	fin2>>s_temp2;fin2.close();fin2.clear();
	fin3>>s_temp3;fin3.close();fin3.clear();
	fin4>>s_temp4;fin4.close();fin4.clear();
	fin5>>s_temp5;fin5.close();fin5.clear();
	fin6>>s_temp6;fin6.close();fin6.clear();

	cout<<"根据情感程度词库分类结果如下："<<endl;
    LIB[1]=LIB[2]=LIB[3]=LIB[4]=LIB[5]=LIB[6]=0;
	
	for(i=0;i<=keyword_num-1;i++)
	{
		//Keywords[i].s="、"+Keywords[i].s+"、";
		Keywords[i].libnum[0]=1;//词库中没有该词
		if (s_temp1.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[1]=1;
			Keywords[i].libnum[0]=0;
			LIB[1]++;
			//cout<<endl<<s_temp1.find(Keywords[i].s)<<endl;
			//cout<<Keywords[i].s<<"在1中找到了";
		}
		else
			Keywords[i].libnum[1]=0;
		if (s_temp2.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[2]=1;
			Keywords[i].libnum[0]=0;
			LIB[2]++;
		}
		else
			Keywords[i].libnum[2]=0;
		if (s_temp3.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[3]=1;
			Keywords[i].libnum[0]=0;
			LIB[3]++;
		}
		else
			Keywords[i].libnum[3]=0;
		//cout<<endl<<s_temp3.find(Keywords[i].s)<<endl;
		if (s_temp4.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[4]=1;
			Keywords[i].libnum[0]=0;
			//cout<<endl<<s_temp4.find(Keywords[i].s)<<endl;
			LIB[4]++;
		}
		else
			Keywords[i].libnum[4]=0;
		if (s_temp5.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[5]=1;
			Keywords[i].libnum[0]=0;
			LIB[5]++;
		}
		else
			Keywords[i].libnum[5]=0;
		if (s_temp6.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[6]=1;
			Keywords[i].libnum[0]=0;
			LIB[6]++;
		}
		else
			Keywords[i].libnum[6]=0;
	}
	for(i=0;i<=6;i++)
		cout<<LIB[i]<<"  ";
	for(i=0;i<=keyword_num-1;i++)
	{
		if(Keywords[i].libnum[0]==1)
			cout<<Keywords[i].s<<":词库中无该词！";
		else
		{
			cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<"  :属于词库";
			for(j=0;j<=6;j++)
				if(Keywords[i].libnum[j]==1)
					cout<<j;
		}
		cout<<endl;
	}
}

/*******
void SplitGBK(char *sInput)
{//分词演示

	//初始化分词组件
	if(!NLPIR_Init("..",0))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!~~~\n");
		return ;
	}

	ICTCLAS_SetPOSmap(ICT_POS_MAP_SECOND);

	//char sSentence[5000]="ICTCLAS在国内973专家组组织的评测中活动获得了第一名，在第一届国际中文处理研究机构SigHan组织的评测中都获得了多项第一名。";
	const char * sResult;


	int nCount;
	ICTCLAS_ParagraphProcessA(sInput,&nCount);
	printf("nCount=%d\n",nCount);
	nCount = ICTCLAS_GetParagraphProcessAWordCount(sInput);
	const result_t *pResult=ICTCLAS_ParagraphProcessA(sInput,&nCount);

	int i=1;
	char *sWhichDic;
	for(i=0;i<nCount;i++)
	{
		sWhichDic="";
		switch (pResult[i].word_type)
		{
		case 0:
			sWhichDic = "核心词典";
			break;
		case 1:
			sWhichDic = "用户词典";
			break;
		case 2:
			sWhichDic = "专业词典";
			break;
		default:
			break;
		}
		printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%s, Word:%s\n",
			i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID, sWhichDic,sInput+pResult[i].start );
	}
	while(_stricmp(sInput,"q")!=0)
	{
		sResult = ICTCLAS_ParagraphProcess(sInput,1);
		printf("%s\nInput string now('q' to quit)!\n", sResult);// 
		gets(sInput);
	}
	
	//导入用户词典前
	printf("未导入用户词典：\n");
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);

	//导入用户词典后
	printf("\n导入用户词典后：\n");
	nCount = ICTCLAS_ImportUserDict("userdic.txt");//userdic.txt覆盖以前的用户词典
	//保存用户词典
	ICTCLAS_SaveTheUsrDic();
	printf("导入%d个用户词。\n", nCount);
	
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);

	//动态添加用户词
	printf("\n动态添加用户词后：\n");
	ICTCLAS_AddUserWord("计算机学院   xueyuan");
	ICTCLAS_SaveTheUsrDic();
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);


	//对文件进行分词
	//ICTCLAS_FileProcess("test2.txt","test2_result.txt",1);
	//ICTCLAS_FileProcess("testGBK.txt","testGBK_result.txt",1);


	//释放分词组件资源
	ICTCLAS_Exit();
}

/*************************************************
void SplitGBK_Fanti(const char *sInput)
{//分词演示

	//初始化分词组件
	if(!ICTCLAS_Init("",GBK_FANTI_CODE))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}

	ICTCLAS_SetPOSmap(ICT_POS_MAP_SECOND);

	char sSentence[5000]="ICTCLAS在国内专家组组织的评测中活动获得了第一名，在第一届国际中文处理研究机构SigHan组织的评测中都获得了多项第一名。ICTCLAS在國內專家組組織的評測中活動獲得了第一名，在第一屆國際中文處理研究機構SigHan組織的評測中都獲得了多項第一名。";
	const char * sResult;


	int nCount;
	ICTCLAS_ParagraphProcessA(sSentence,&nCount);
	printf("nCount=%d\n",nCount);
	int count = ICTCLAS_GetParagraphProcessAWordCount(sSentence);
	const result_t *pResult=ICTCLAS_ParagraphProcessA(sSentence,&nCount);

	int i=1;
	char *sWhichDic;
	for(i=0;i<nCount;i++)
	{
		sWhichDic="";
		switch (pResult[i].word_type)
		{
		case 0:
			sWhichDic = "核心词典";
			break;
		case 1:
			sWhichDic = "用户词典";
			break;
		case 2:
			sWhichDic = "专业词典";
			break;
		default:
			break;
		}
		printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%s, Word:%s\n",
			i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID, sWhichDic,sSentence+pResult[i].start );
	}
	while(_stricmp(sSentence,"q")!=0)
	{
		sResult = ICTCLAS_ParagraphProcess(sSentence,0);
		printf("%s\nInput string now('q' to quit)!\n", sResult);// 
		scanf("%s",sSentence);
	}
	
	//导入用户词典前
	printf("未导入用户词典：\n");
	sResult = ICTCLAS_ParagraphProcess(sInput, 0);
	printf("%s\n", sResult);

	//导入用户词典后
	printf("\n导入用户词典后：\n");
	nCount = ICTCLAS_ImportUserDict("userdic.txt");//userdic.txt覆盖以前的用户词典
	//保存用户词典
	ICTCLAS_SaveTheUsrDic();
	printf("导入%d个用户词。\n", nCount);
	
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);

	//动态添加用户词
	printf("\n动态添加用户词后：\n");
	ICTCLAS_AddUserWord("计算机学院   xueyuan");
	ICTCLAS_SaveTheUsrDic();
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);


	//对文件进行分词
	ICTCLAS_FileProcess("test2.txt","test2_result.txt",1);
	ICTCLAS_FileProcess("testGBK.txt","testGBK_result.txt",1);


	//释放分词组件资源
	ICTCLAS_Exit();
}
void SplitBIG5()
{
	//初始化分词组件
	if(!ICTCLAS_Init("",BIG5_CODE))//数据在当前路径下，设置为BIG5编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("testBIG.txt","testBIG_result.txt");
	ICTCLAS_Exit();
}
void SplitUTF8()
{
	//初始化分词组件
	if(!ICTCLAS_Init("",UTF8_CODE))//数据在当前路径下，设置为UTF8编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("testUTF.txt","testUTF_result.txt");
	//ICTCLAS_FileProcess("test.xml","testUTF_result.xml");


	FILE *fp=fopen("TestUTF8-bigfile.txt","rt");
	if (fp==NULL)
	{
		printf("Error Open TestUTF8-bigfile.txt\n");
		ICTCLAS_Exit();
		return ;
	}
	char sLine[10241];
	int i,nCount,nDocID=1;
	//result_t res[1000];
	//while (fgets(sLine,10240,fp))
	{
		CICTCLAS *pICTCLAS=new CICTCLAS;
	/*	
		int nCountA=pICTCLAS->GetParagraphProcessAWordCount(sLine);
		pICTCLAS->ParagraphProcessAW(nCountA,res);
		for(i=0;i<nCountA;i++)
		{
			printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d\n",
				i+1, res[i].start, res[i].length, res[i].iPOS, res[i].word_ID);
		}

	
		fseek(fp,0,SEEK_END);
		int nSize=ftell(fp);

		fseek(fp,0,SEEK_SET);
		fread(sLine,nSize,1,fp);
		sLine[nSize]=0;
		const result_t *pResult=pICTCLAS->ParagraphProcessA(sLine,&nCount);
	    i=1;

		for(i=0;i<500&&i<nCount;i++)
		{
 			printf("\nNo.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d\n",
 				i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID);
			fwrite(sLine+pResult[i].start,sizeof(char),pResult[i].length,stdout);
		}
		delete pICTCLAS;
		printf("Processed docs %d\r",nDocID++);
	}

	ICTCLAS_Exit();
}

void testMultiThread()
{
	//初始化分词组件
	if(!ICTCLAS_Init("",UTF8_CODE))//数据在当前路径下，设置为UTF8编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("E:\\ictclas2010\\反馈\\中科院分词初体验\\long_utf8.txt","E:\\ictclas2010\\反馈\\中科院分词初体验\\long_utf8_result.txt");
	ICTCLAS_FileProcess("E:\\ictclas2010\\反馈\\中科院分词初体验\\long.txt","E:\\ictclas2010\\反馈\\中科院分词初体验\\long_result.txt");	
	ICTCLAS_Exit();
}*****************/
int main()
{
	int cl;
	testWord(GBK_CODE);
	KW_Topic_Classify();
	int ccount_topic[10]={517,460,461,542,550,489,517,331,496,452};
	cl=NaiveBayes(10,ccount_topic,4815);
	switch(cl)
	{
		case 1:cout<<"段落属于生活类！"<<endl;break;
		case 2:cout<<"段落属于医疗保健类！"<<endl;break;
		case 3:cout<<"段落属于体育类！"<<endl;break;
		case 4:cout<<"段落属于娱乐类！"<<endl;break;
		case 5:cout<<"段落属于旅游类！"<<endl;break;
		case 6:cout<<"段落属于政治类！"<<endl;break;
		case 7:cout<<"段落属于科技类！"<<endl;break;
		case 8:cout<<"段落属于军事类！"<<endl;break;
		case 9:cout<<"段落属于财经类！"<<endl;break;
		case 10:cout<<"段落属于教育文化类！"<<endl;break;
		default:cout<<"无法识别！"<<endl;
	}
	
   KW_Emo_Classify();
	int ccount_emo[2]={3922,3866};//,4727};
	//int ccount_emo[5]={2786,1134,3168,697,4727};
	cl=NaiveBayes(2,ccount_emo,7788);
	switch(cl)
	{
		case 1:cout<<"段落属于负面情感类！"<<endl;break;
		case 2:cout<<"段落属于正面情感类！"<<endl;break;
		case 3:cout<<"段落属于中性情感类！"<<endl;break;
		default:cout<<"无法识别！"<<endl;
	}
	//KW_Emo_Level_Classify();
	/*int ccount_level[6]={69,42,35,29,12,30};
	cl=NaiveBayes(6,ccount_level,217);
	switch(cl)
	{
		case 1:cout<<"情感程度属于“极其”级别！"<<endl;break;
		case 2:cout<<"情感程度属于“很”级别！"<<endl;break;
		case 3:cout<<"情感程度属于“比较”级别！"<<endl;break;
		case 4:cout<<"情感程度属于“稍微”级别！"<<endl;break;
		case 5:cout<<"情感程度属于“欠”级别！"<<endl;break;
		case 6:cout<<"情感程度属于“过度”级别！"<<endl;break;
		default:cout<<"无法识别！"<<endl;
	}*/
	system("pause");
	return 1;
}

