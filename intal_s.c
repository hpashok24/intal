#include "intal.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

void* intal_create(const char *str)
{
  char *string;
  int length=strlen(str);
  int i;
  int count=0;
  for(i=0;i<length;i++)
  {
    if(str[i]!='0')
     break;
    count++;
  }
  int length_new_string;
  int j=0;
  if(count==length)
   length_new_string=1;
  else
  length_new_string=length-count;
  string=(char *)malloc((length_new_string+1)*sizeof(char));
  if(length_new_string==1 && str[0]=='0')
  {
    string[0]=str[length-1];
    string[1]='\0';
  }
  else
  {
    for(i=count;str[i]!='\0';i++)
     string[j++]=str[i];
    string[j]='\0';
  }
  //printf("%s %d\n",string,strlen(string));
  return (void *)string;
}

char* intal2str(void* intal)
{
  char *string;
  string=(char *)intal;
  return string;
}

void intal_destroy(void* intal)
{
  free(intal);
}

int intal_compare(void* intal1, void* intal2)
{
  //Returns -1, 0, +1
  //Returns 0 when both are equal.
  //Returns +1 when intal1 is greater, and -1 when intal2 is greater.
  char *string1,*string2;
  string1=(char *)intal1;
  string2=(char *)intal2;
  int string1_len=strlen(string1);
  int string2_len=strlen(string2);
  int string1_digit,string2_digit;
  int i,j;
  if(string1_len>string2_len)
   return 1;
  else if(string2_len>string1_len)
   return -1;
  else
  {
   //int flag=0;
    //printf("SDF\n");
   for(i=0,j=0;i<string1_len,j<string2_len;i++,j++)
   {
     string1_digit=string1[i]-'0';
     string2_digit=string2[j]-'0';
     if(string1_digit!=string2_digit)
    {
      if(string1_digit>string2_digit)
       return 1;
      else
       return -1;
    }
  }
   return 0;
}
}

void* intal_increment(void* intal)
{

  char *string=(char *)intal;
  //printf("old string lenght=%d\n",strlen(string));
  int string_len=strlen(string);
  int i;
  int digit;
  int temp;
  int carry=0;
  if(string_len==1)
  {
    digit=string[0]-'0';
    digit=digit+1;
    if(digit<=9)
     string[0]=digit+'0';
    else
    {
      string=(char *)malloc((string_len+2)*sizeof(char));
      string[0]='1';
      string[1]='0';
      string[2]='\0';
    }
  }
  else
 {
  for(i=string_len-1;i>0;i--)
  {
    digit=string[i]-'0';
    if(i==string_len-1)
     temp=digit+carry+1;
    else
     temp=digit+carry;
    if(temp==10)
    {
      carry=1;
      string[i]='0';
    }
    else
    {
      carry=0;
      string[i]=temp+'0';
  }
}
char *temp_string=(char *)malloc((string_len+1)*sizeof(char));
digit=string[0]-'0';
temp=digit+carry;
int j;
if(temp<=9)
 string[0]=temp+'0';
else
{
  for(i=0;i<string_len;i++)
    temp_string[i]=string[i];
  temp_string[i]='\0';
  string=(char *)malloc((string_len+2)*sizeof(char));
  string[0]='1';
  string[1]='0';
  j=2;
  for(i=1;i<string_len;i++)
   string[j++]=temp_string[i];
  string[j]='\0';
}
free(temp_string);
}

//printf("new string lenght=%d\n",strlen(string));
//printf("%s\n",string);
 return (void *)string;
}

void* intal_add(void* intal1, void* intal2)
{
  char *string1=(char *)intal1;
  char *string2=(char *)intal2;
  int string1_len=strlen(string1);
  int string2_len=strlen(string2);
  int string3_len;
  int flag=0;
  if(string1_len>=string2_len)
   string3_len=string1_len+1;
  else
  {
   string3_len=string2_len+1;
   flag=1;
 }
  char *add_string=(char *)malloc(string3_len*sizeof(char));
  int carry=0;
  int i,j,k;
  int str1digit,str2digit,digit;
  char *temp_string=(char *)malloc((string3_len)*sizeof(char));
  if(string1_len==string2_len)
  {
    j=string1_len-1;
    for(i=string1_len-1;i>0;i--)
    {
      str1digit=string1[i]-'0';
      str2digit=string2[i]-'0';
      digit=str1digit+str2digit+carry;
      if(digit<=9)
      {
        add_string[j--]=digit+'0';
        carry=0;
      }
      else
      {
        add_string[j--]=(digit%10)+'0';
        carry=1;
      }
    }
    digit=(string1[0]-'0')+(string2[0]-'0')+carry;
    if(digit<=9)
    {
      add_string[0]=digit+'0';
      add_string[string3_len]='\0';
    }
    else
    {
      for(i=0;i<string3_len;i++)
        temp_string[i]=add_string[i];
      temp_string[i]='\0';
      add_string=(char *)malloc((string3_len+1)*sizeof(char));
      add_string[0]='1';
      add_string[1]=(((string1[0]-'0')+(string2[0]-'0')+carry)%10)+'0';
      j=2;
      for(i=1;i<string3_len;i++)
       add_string[j++]=temp_string[i];
      add_string[j]='\0';
    }
  }
  else
  {
    //printf("inside else\n");
    if(flag==0)
    {

      j=string1_len-1;
      char *temp=(char *)malloc((string1_len+1)*sizeof(char));
      for(i=0;i<(string1_len-string2_len);i++)
      {
        temp[i]='0';
      }
      for(k=0;k<string2_len;k++)
       temp[i++]=string2[k];
      //printf("temp=%s\n",temp);
      for(i=string1_len-1;i>0;i--)
      {
        str1digit=string1[i]-'0';
        str2digit=temp[i]-'0';
        digit=str1digit+str2digit+carry;
        if(digit<=9)
        {
          add_string[j--]=digit+'0';
          carry=0;
        }
        else
        {
          add_string[j--]=(digit%10)+'0';
          carry=1;
        }
      }
      digit=(string1[0]-'0')+(temp[0]-'0')+carry;
      if(digit<=9)
      {
        add_string[0]=digit+'0';
        add_string[string3_len]='\0';
      }
      else
      {
        for(i=0;i<string3_len;i++)
          temp_string[i]=add_string[i];
        temp_string[i]='\0';
        add_string=(char *)malloc((string3_len+1)*sizeof(char));
        add_string[0]='1';
        add_string[1]=(((string1[0]-'0')+(temp[0]-'0')+carry)%10)+'0';
        j=2;
        for(i=1;i<string3_len;i++)
         add_string[j++]=temp_string[i];
        add_string[j]='\0';
      }

    }
    else
    {

            j=string2_len-1;
            char *temp=(char *)malloc((string2_len+1)*sizeof(char));
            for(i=0;i<(string2_len-string1_len);i++)
            {
              temp[i]='0';
            }
            for(k=0;k<string1_len;k++)
             temp[i++]=string1[k];
            //printf("temp=%s\n",temp);
            for(i=string2_len-1;i>0;i--)
            {
              str2digit=string2[i]-'0';
              str1digit=temp[i]-'0';
              digit=str1digit+str2digit+carry;
              if(digit<=9)
              {
                add_string[j--]=digit+'0';
                carry=0;
              }
              else
              {
                add_string[j--]=(digit%10)+'0';
                carry=1;
              }
            }
            digit=(string2[0]-'0')+(temp[0]-'0')+carry;
            if(digit<=9)
            {
              add_string[0]=digit+'0';
              add_string[string3_len]='\0';
            }
            else
            {
              for(i=0;i<string3_len;i++)
                temp_string[i]=add_string[i];
              temp_string[i]='\0';
              add_string=(char *)malloc((string3_len+1)*sizeof(char));
              add_string[0]='1';
              add_string[1]=(((string2[0]-'0')+(temp[0]-'0')+carry)%10)+'0';
              j=2;
              for(i=1;i<string3_len;i++)
               add_string[j++]=temp_string[i];
              add_string[j]='\0';
            }

    }
  }
  //printf("%s\n",add_string);
  return (void *)add_string;

}

void* intal_decrement(void* intal)
{
  char *string=(char *)intal;
  int string_len=strlen(string);
  int i,j;
  int borrow=0;
  int digit=string[string_len-1]-'0';
  if(digit>0)
  {
    digit=digit-1;
    string[string_len-1]=digit+'0';
  }
  else
  {
    //printf("Inside else\n");
    borrow=1;
    digit=9;
    string[string_len-1]=digit+'0';
    for(i=string_len-2;i>0;i--)
    {
      digit=string[i]-'0';
      if(borrow==1)
    {
      if(digit!=0)
      {
        digit=digit-1;
        string[i]=digit+'0';
        borrow=0;
      }
      else
      {
        string[i]='9';
        borrow=1;
      }
    }
  }
    if(string[0]=='1' &&  borrow==1)
    {
      //printf("Inside if\n");
      char *temp=(char *)malloc(string_len*sizeof(char));
      for(i=0;i<string_len;i++)
       temp[i]=string[i];
      char *string=(char *)malloc(string_len*sizeof(char));
       string[0]='9';
       j=1;
      for(i=2;i<string_len;i++)
      {
        string[j++]=temp[i];
      }
      string[j]='\0';
      return (void *)string;
    }
    else if(borrow==1 && string[0]!='1')
    {
      //printf("dfs\n");
      digit=string[0]-'0';
      digit=digit-1;
      string[0]=digit+'0';
    }
  }
  return (void *)string;
}

void* intal_diff(void *intal1,void *intal2)
{
  char *max_string;
  char *string1=(char *)intal1;
  char *string2=(char *)intal2;
  char *temp;
  max_string=(intal_compare(intal1, intal2) > 0) ? intal2str(intal1) : intal2str(intal2);
  if(strcmp(max_string,string1))
  {
    temp=string1;
    string1=string2;
    string2=temp;
  }
  char *string2_new;
  int i,j;
  j=strlen(string2)-1;
  if(strlen(string1)!=strlen(string2))
  {
    string2_new=(char *)malloc((strlen(string1)+1)*sizeof(char));
    string2_new[strlen(string1)+1]='\0';
    for(i=strlen(string1)-1;i>=strlen(string1)-strlen(string2);i--)
    {
      string2_new[i]=string2[j];
      j--;
    }
    for(;i>=0;i--)
    {
      string2_new[i]='0';
    }
  }
  else
   string2_new=string2;
  string2=string2_new;
  //printf("%s\n",string2);
  int digit1,digit2,carry;
  char *diff=(char *)malloc(sizeof((string1)+1)*sizeof(char));
  diff[strlen(string1)+1]='\0';
  int borrow=0;
  for(i=strlen(string1)-1;i>=0;i--)
  {
    digit1=string1[i]-'0';
    digit2=string2[i]-'0';
    if(digit1>=digit2)
    {
      digit1=digit1-borrow;
      if(digit1>=digit2)
      {
       diff[i]=(digit1-digit2)+'0';
       borrow=0;
      }
      else
      {
        digit1=digit1+borrow;
        digit1=digit1+10-borrow;
        diff[i]=(digit1-digit2)+'0';
        borrow=1;
      }
   }
    else
    {
      digit1=digit1+10-borrow;
      diff[i]=(digit1-digit2)+'0';
      borrow=1;
    }
  }
  int len=strlen(diff);
  if(diff[0]=='0' && len!=1)
  {
    for(i=1;i<len+1;i++)
     diff[i-1]=diff[i];
  }
  printf("diff finished");
  return (void *)diff;
}

void* intal_multiply(void* intal1, void* intal2)
{
  char *string1=(char *)intal1;
  char *string2=(char *)intal2;
  int string1_len=strlen(string1);
  //printf("%d\n",string1_len);
  int string2_len=strlen(string2);
  int i;
  int flag=0;
  char *temp=(char *)malloc(sizeof(char)*(string1_len+2));
  for(i=0;i<=string1_len+1;i++)
   temp[i]='0';
  temp[string1_len+1]='\0';
  int count=0;
  int j;
  int digit1,digit2;
  int carry=0;
  int temp_res;
  int k;
  //int flag=0;
    carry=0;
    digit2=string2[string2_len-1]-'0';
    k=string1_len;
    for(j=string1_len-1;j>0;j--)
    {
      digit1=string1[j]-'0';
      temp_res=digit1*digit2+carry;
      if(temp_res>9)
      {
        carry=temp_res/10;
        temp_res=temp_res%10;
      }
      else
      {
        carry=0;
      }
      temp[k--]=temp_res+'0';
    }
    digit1=string1[0]-'0';
    temp_res=digit1*digit2+carry;
    if(temp_res>9)
    {
      carry=temp_res/10;
      temp_res=temp_res%10;
      temp[k--]=temp_res+'0';
      temp[k--]=carry+'0';
    }
    else
    {
      temp[k--]=temp_res+'0';
    }
    char *temp2;
    count=1;
    char *add_char;
    add_char=temp;
    //printf("%c\n",string2[string2_len-2]);
for(i=string2_len-2;i>=0;i--)
{
  digit2=string2[i]-'0';
  carry=0;
  temp2=(char *)malloc(sizeof(char)*(string1_len+2+count));
  for(j=0;j<=string1_len+1+count;j++)
   temp2[j]='0';
  temp2[string1_len+1+count]='\0';
  k=string1_len+count;
  j=count;
  for(;j>0;j--)
   temp2[k--]='0';
  for(j=string1_len-1;j>0;j--)
  {
    digit1=string1[j]-'0';
    temp_res=digit1*digit2+carry;
    if(temp_res>9)
    {
      carry=temp_res/10;
      temp_res=temp_res%10;
    }
    else
    {
      carry=0;
    }
    temp2[k--]=temp_res+'0';
  }
  digit1=string1[0]-'0';
  temp_res=digit1*digit2+carry;
  if(temp_res>9)
  {
    carry=temp_res/10;
    temp_res=temp_res%10;
    temp2[k--]=temp_res+'0';
    temp2[k--]=carry+'0';
  }
  else
  {
    temp2[k--]=temp_res+'0';
  }
  count++;
  if(flag==0)
  {
    add_char=(char *)intal_add((void *)temp,(void *)temp2);
    flag=1;
  }
  else
  {
    add_char=(char *)intal_add((void *)add_char,(void *)temp2);
  }
}

if(add_char[0]=='0' && strlen(add_char)!=1)
{
  for(i=1;i<strlen(add_char)+1;i++)
   add_char[i-1]=add_char[i];
}
printf("%s\n",add_char);
return (void *)temp;
}
