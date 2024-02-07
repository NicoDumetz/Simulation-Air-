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

int charal(char c)
{
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

int charnum(char c)
{
    return (c >= 48 && c <= 57);
}

int count_word(char const *str)
{
    int compt = 0;
    int i = 0;

    if ( charal(str[0]) == 1 || charnum(str[0]) == 1)
        compt = 1;
    else
        compt = 0;
    if ( my_strlen(str) == 0)
        return 0;
    for ( i = 0; str[i]; i++ ) {
        if ((charal(str[i]) != 1 && charnum(str[i]) != 1) &&
            (charal(str[i + 1]) == 1 || charnum(str[i + 1])))
            compt++;
    }
    return compt;
}

int word_after(char const *str, int i)
{
    int compt = 0;

    for ( i; charal(str[i]) == 1 || charnum(str[i]) == 1;i++) {
        compt++;
    }
    return compt;
}

static char **set_last(char **li_final, char const *str)
{
    li_final[count_word(str)] = 0;
    return li_final;
}

char **my_str_to_word_array(char const *str)
{
    char **li_final;
    char *temp;
    int index;
    int col = 0;
    int k;

    li_final = malloc( (count_word(str) + 1)* sizeof(char *));
    for ( index = 0; str[index] != '\0' && col <= count_word(str); index++) {
        temp = malloc( (word_after(str, index) + 1)*sizeof(char *));
        for (k = 0; charal(str[index]) == 1 || charnum(str[index]) == 1 ; k++){
            temp[k] = str[index];
            index++;
        }
        if ( k >= 1) {
            temp[k] = '\0';
            li_final[col] = temp;
            col++;
        }
    }
    return set_last(li_final, str);
}
