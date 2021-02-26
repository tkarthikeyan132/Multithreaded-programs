#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<time.h>

void CreateHistogram(char * content, int size);

int main  () {
  char * content = "CED18I064 !!!!!! T Karthikeyan 7438947#$^&#$%#^&&*&*@~!#%$?}{:>}?";
  printf("%s\n",content);
  printf("-------------Histogram generator-------------\n");
  CreateHistogram(content, strlen(content));  
  return 0;
} 

void CreateHistogram(char * content, int size) { 
    
  int pid1, pid2, pid3, pid4, pid5, pid6, pid7, pid8, pid9, pid10, pid11, pid12, pid13, pid14, pid15, pid16, pid17, pid18, pid19, pid20, pid21, pid22, pid23, pid24, pid25, wpid;
  int status = 0;

  // parent will take care of remaining characters
  // children have to take care of characters in set of 5
  pid1 = fork();
  if (pid1 == 0)// Computes the frequency of ASCII 33 - 37
  {
    int count[5] = {0,0,0,0,0};
    for(int i = 0; i < size; i++) 
    { 
      int temp = (content[i]-33);
      if (temp >=0 && temp <=4) 
      {
        count[temp]++;
      }
    }
    for(int k = 0; k < 5; k++)
    {
        printf("%c :",33+k);
        for(int j = 0; j < count[k]; j++)
            printf("(^_^)");
        printf("   (%d)\n", count[k]);
    }
  }
  else
  {
    pid2 = fork();
    if (pid2 == 0)// Computes the frequency of ASCII 38 - 42
    {
        int count[5] = {0,0,0,0,0};
        for(int i = 0; i < size; i++) 
        { 
        int temp = (content[i]-38);
        if (temp >=0 && temp <=4) 
        {
            count[temp]++;
        }
        }
        for(int k = 0; k < 5; k++)
        {
            printf("%c :",38+k);
            for(int j = 0; j < count[k]; j++)
                printf("(^_^)");
            printf("   (%d)\n", count[k]);
        }
    }
    else
    {
      pid3 = fork();
      if (pid3 == 0)// Computes the frequency of ASCII 43 - 47
      {
        int count[5] = {0,0,0,0,0};
        for(int i = 0; i < size; i++) 
        { 
        int temp = (content[i]-43);
        if (temp >=0 && temp <=4) 
        {
            count[temp]++;
        }
        }
        for(int k = 0; k < 5; k++)
        {
            printf("%c :",43+k);
            for(int j = 0; j < count[k]; j++)
                printf("(^_^)");
            printf("   (%d)\n", count[k]);
        }
      }
      else
      {
        pid4 = fork();
        if (pid4 == 0)// Computes the frequency of ASCII 48 - 52
        {
            int count[5] = {0,0,0,0,0};
            for(int i = 0; i < size; i++) 
            { 
            int temp = (content[i]-48);
            if (temp >=0 && temp <=4) 
            {
                count[temp]++;
            }
            }
            for(int k = 0; k < 5; k++)
            {
                printf("%c :",48+k);
                for(int j = 0; j < count[k]; j++)
                    printf("(^_^)");
                printf("   (%d)\n", count[k]);
            }
        }
        else
        {
          pid5 = fork();
          if (pid5 == 0)// Computes the frequency of ASCII 53 - 57
          {
            int count[5] = {0,0,0,0,0};
            for(int i = 0; i < size; i++) 
            { 
            int temp = (content[i]-53);
            if (temp >=0 && temp <=4) 
            {
                count[temp]++;
            }
            }
            for(int k = 0; k < 5; k++)
            {
                printf("%c :",53+k);
                for(int j = 0; j < count[k]; j++)
                    printf("(^_^)");
                printf("   (%d)\n", count[k]);
            }
          }
          else
          {
            pid6 = fork();
            if (pid6 == 0)// Computes the frequency of ASCII 58 - 62
            {
                int count[5] = {0,0,0,0,0};
                for(int i = 0; i < size; i++) 
                { 
                int temp = (content[i]-58);
                if (temp >=0 && temp <=4) 
                {
                    count[temp]++;
                }
                }
                for(int k = 0; k < 5; k++)
                {
                    printf("%c :",58+k);
                    for(int j = 0; j < count[k]; j++)
                        printf("(^_^)");
                    printf("   (%d)\n", count[k]);
                }
            }
            else
            {
              pid7 = fork();
              if (pid7 == 0)// Computes the frequency of ASCII 63 - 67
              {
                int count[5] = {0,0,0,0,0};
                for(int i = 0; i < size; i++) 
                { 
                int temp = (content[i]-63);
                if (temp >=0 && temp <=4) 
                {
                    count[temp]++;
                }
                }
                for(int k = 0; k < 5; k++)
                {
                    printf("%c :",63+k);
                    for(int j = 0; j < count[k]; j++)
                        printf("(^_^)");
                    printf("   (%d)\n", count[k]);
                }
              }
              else
              {
                pid8 = fork();
                if (pid8 == 0)// Computes the frequency of ASCII 68 - 72
                {
                    int count[5] = {0,0,0,0,0};
                    for(int i = 0; i < size; i++) 
                    { 
                    int temp = (content[i]-68);
                    if (temp >=0 && temp <=4) 
                    {
                        count[temp]++;
                    }
                    }
                    for(int k = 0; k < 5; k++)
                    {
                        printf("%c :",68+k);
                        for(int j = 0; j < count[k]; j++)
                            printf("(^_^)");
                        printf("   (%d)\n", count[k]);
                    }
                }
                else
                {
                  pid9 = fork();
                  if (pid9 == 0)// Computes the frequency of ASCII 73-77
                  {
                    int count[5] = {0,0,0,0,0};
                    for(int i = 0; i < size; i++) 
                    { 
                    int temp = (content[i]-73);
                    if (temp >=0 && temp <=4) 
                    {
                        count[temp]++;
                    }
                    }
                    for(int k = 0; k < 5; k++)
                    {
                        printf("%c :",73+k);
                        for(int j = 0; j < count[k]; j++)
                            printf("(^_^)");
                        printf("   (%d)\n", count[k]);
                    }
                  }
                  else
                  {
                    pid10 = fork();
                    if (pid10 == 0)// Computes the frequency of ASCII 78-82
                    {
                        int count[5] = {0,0,0,0,0};
                        for(int i = 0; i < size; i++) 
                        { 
                        int temp = (content[i]-78);
                        if (temp >=0 && temp <=4) 
                        {
                            count[temp]++;
                        }
                        }
                        for(int k = 0; k < 5; k++)
                        {
                            printf("%c :",78+k);
                            for(int j = 0; j < count[k]; j++)
                                printf("(^_^)");
                            printf("   (%d)\n", count[k]);
                        }
                    } 
                    else
                    {
                      pid11 = fork();
                      if (pid11 == 0)// Computes the frequency of ASCII 83-87
                      {
                        int count[5] = {0,0,0,0,0};
                        for(int i = 0; i < size; i++) 
                        { 
                        int temp = (content[i]-83);
                        if (temp >=0 && temp <=4) 
                        {
                            count[temp]++;
                        }
                        }
                        for(int k = 0; k < 5; k++)
                        {
                            printf("%c :",83+k);
                            for(int j = 0; j < count[k]; j++)
                                printf("(^_^)");
                            printf("   (%d)\n", count[k]);
                        }
                      } 
                      else
                      {   
                        pid12 = fork();
                        if (pid12 == 0)// Computes the frequency of ASCII 88-92
                        {
                            int count[5] = {0,0,0,0,0};
                            for(int i = 0; i < size; i++) 
                            { 
                            int temp = (content[i]-88);
                            if (temp >=0 && temp <=4) 
                            {
                                count[temp]++;
                            }
                            }
                            for(int k = 0; k < 5; k++)
                            {
                                printf("%c :",88+k);
                                for(int j = 0; j < count[k]; j++)
                                    printf("(^_^)");
                                printf("   (%d)\n", count[k]);
                            }
                        } 
                        else
                        {
                          pid13 = fork();
                          if (pid13 == 0)// Computes the frequency of ASCII 93-97
                          {
                            int count[5] = {0,0,0,0,0};
                            for(int i = 0; i < size; i++) 
                            { 
                            int temp = (content[i]-93);
                            if (temp >=0 && temp <=4) 
                            {
                                count[temp]++;
                            }
                            }
                            for(int k = 0; k < 5; k++)
                            {
                                printf("%c :",93+k);
                                for(int j = 0; j < count[k]; j++)
                                    printf("(^_^)");
                                printf("   (%d)\n", count[k]);
                            }
                          } 
                          else
                          { 
                            pid14 = fork();
                            if (pid14 == 0)// Computes the frequency of ASCII 98-102
                            {
                                int count[5] = {0,0,0,0,0};
                                for(int i = 0; i < size; i++) 
                                { 
                                int temp = (content[i]-98);
                                if (temp >=0 && temp <=4) 
                                {
                                    count[temp]++;
                                }
                                }
                                for(int k = 0; k < 5; k++)
                                {
                                    printf("%c :",98+k);
                                    for(int j = 0; j < count[k]; j++)
                                        printf("(^_^)");
                                    printf("   (%d)\n", count[k]);
                                }
                            } 
                            else
                            { 
                              pid15 = fork();
                              if (pid15 == 0)// Computes the frequency of ASCII 103-107
                              {
                                int count[5] = {0,0,0,0,0};
                                for(int i = 0; i < size; i++) 
                                { 
                                int temp = (content[i]-103);
                                if (temp >=0 && temp <=4) 
                                {
                                    count[temp]++;
                                }
                                }
                                for(int k = 0; k < 5; k++)
                                {
                                    printf("%c :",103+k);
                                    for(int j = 0; j < count[k]; j++)
                                        printf("(^_^)");
                                    printf("   (%d)\n", count[k]);
                                }
                              } 
                              else
                              {
                                pid16 = fork();
                                if (pid16 == 0)// Computes the frequency of ASCII 108-112
                                {
                                    int count[5] = {0,0,0,0,0};
                                    for(int i = 0; i < size; i++) 
                                    { 
                                    int temp = (content[i]-108);
                                    if (temp >=0 && temp <=4) 
                                    {
                                        count[temp]++;
                                    }
                                    }
                                    for(int k = 0; k < 5; k++)
                                    {
                                        printf("%c :",108+k);
                                        for(int j = 0; j < count[k]; j++)
                                            printf("(^_^)");
                                        printf("   (%d)\n", count[k]);
                                    }
                                } 
                                else
                                {  
                                  pid17 = fork();
                                  if (pid17 == 0)// Computes the frequency of ASCII 113-117
                                  {
                                    int count[5] = {0,0,0,0,0};
                                    for(int i = 0; i < size; i++) 
                                    { 
                                    int temp = (content[i]-113);
                                    if (temp >=0 && temp <=4) 
                                    {
                                        count[temp]++;
                                    }
                                    }
                                    for(int k = 0; k < 5; k++)
                                    {
                                        printf("%c :",113+k);
                                        for(int j = 0; j < count[k]; j++)
                                            printf("(^_^)");
                                        printf("   (%d)\n", count[k]);
                                    }
                                  } 
                                  else
                                  {
                                    pid18 = fork();
                                    if (pid18 == 0)// Computes the frequency of ASCII 118-122
                                    {
                                        int count[5] = {0,0,0,0,0};
                                        for(int i = 0; i < size; i++) 
                                        { 
                                        int temp = (content[i]-118);
                                        if (temp >=0 && temp <=4) 
                                        {
                                            count[temp]++;
                                        }
                                        }
                                        for(int k = 0; k < 5; k++)
                                        {
                                            printf("%c :",118+k);
                                            for(int j = 0; j < count[k]; j++)
                                                printf("(^_^)");
                                            printf("   (%d)\n", count[k]);
                                        }
                                    } 
                                    else // ASCII 123-126
                                    {
                                        while ((wpid = wait(&status)) > 0);
                                        int count[4] = {0,0,0,0};
                                        for(int i = 0; i < size; i++) 
                                        { 
                                        int temp = (content[i]-123);
                                        if (temp >=0 && temp <=3) 
                                        {
                                            count[temp]++;
                                        }
                                        }
                                        for(int k = 0; k < 4; k++)
                                        {
                                            printf("%c :",123+k);
                                            for(int j = 0; j < count[k]; j++)
                                                printf("(^_^)");
                                            printf("   (%d)\n", count[k]);
                                        } 
                                        printf("\n-------------------------------------\n");
                                    }//19
                                  } //18
                                } //17
                              }//16
                            }//15
                          } //14
                        }//13
                      }//12
                    } //11
                  } //10
                } //9
              } //8
            } //7
          } //6
        } //5
      } //4
    } //3
  } //2
} //1










        
