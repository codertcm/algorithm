# count_words_number

```c++

#include <stdio.h>
#include <string.h>
int check(char c)
{
    if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
        return 1;
    else
        return 0;
}
int main()
{
    int i,cnt = 0;
    char s[1000] = {0};
    char pre = ' ';
    gets(s);
    for(i = 0; s[i] != 0; i++)
    {
        if(check(pre) == 0  && check(s[i]) == 1)
        {
            cnt++;
        }
        pre = s[i];
    }
    printf("%d\n",cnt);
    return 0;
}

```
