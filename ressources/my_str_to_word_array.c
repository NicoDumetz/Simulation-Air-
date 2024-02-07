/*
** EPITECH PROJECT, 2023
** STR_TO_ARRAY
** File description:
** Write a function that splits a string into words.
** Separators will all be non-alphanumeric characters.
** The function returns an array in which each cell
** contains the address of a string (representing a word).
** The last cell must be null to terminate the array.
** The function must be prototyped as follows:
*/

#include "../include/my_radar.h"

int charal2(char c)
{
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

int charnum2(char c)
{
    return (c >= 48 && c <= 57);
}

int count_word2(char const *str)
{
    int compt = 0;
    int i = 0;

    if (charal2(str[0]) == 1 || charnum2(str[0]) == 1)
        compt = 1;
    else
        compt = 0;
    if (my_strlen(str) == 0)
        return 0;
    for (i = 0; str[i]; i++) {
        if ((charal2(str[i]) != 1 && charnum2(str[i]) != 1) &&
            (charal2(str[i + 1]) == 1 || charnum2(str[i + 1])))
            compt++;
    }
    return compt;
}

int word_after2(char const *str, int i)
{
    int compt = 0;

    for (i; charal2(str[i]) == 1 || charnum2(str[i]) == 1; i++) {
        compt++;
    }
    return compt;
}

static char **set_array(char **li_final, char *str, int len)
{
    int index;
    char *temp;
    int col = 0;
    int k;

    for (index = 0; str[index] != '\0' && col <= len; index++) {
        temp = malloc((word_after2(str, index) + 1) * sizeof(char *));
        for (k = 0; charal2(str[index]) == 1 || charnum2(str[index]) == 1; k
        ++){
            temp[k] = str[index];
            index++;
        }
        if (k >= 1) {
            temp[k] = '\0';
            li_final[col] = temp;
            col++;
        }
    }
    return li_final;
}

char **my_str_to_word_array(char *str)
{
    char **li_final;
    int len = count_word2(str);

    li_final = malloc((len + 1) * sizeof(char *));
    li_final = set_array(li_final, str, len);
    li_final[len] = 0;
    return li_final;
}
