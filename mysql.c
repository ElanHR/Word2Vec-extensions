#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>

main()
{
        printf("Hello World");
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;

    unsigned int num_fields;
    unsigned int i;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql, "localhost", "root", "root", "wordnet",0,NULL,0))
        {
                printf( "Failed to connect to localhost: Error: %s\n", mysql_error(&mysql));
                exit(1);
        }
    if(mysql_select_db(&mysql,"wordnet")==0)/*success*/
    {
            printf( "Database wordnet Selected\n");
    }
    else 
    {
            printf( "Failed to connect to Database wordnet: Error: %s\n", mysql_error(&mysql));
    }
    /* now call other API's*/
    //char* query = "select lemma from wordnet.words where wordid in (select wordid from wordnet.senses where synsetid in (select synsetid from wordnet.senses where wordid in (select wordid from wordnet.words where lemma = 'bird')))";
    char* query = "select lemma from words where wordid in (select wordid from senses where synsetid in (select synsetid from senses where wordid in (select wordid from words where lemma = 'bird')))";
    // if(!mysql_query(&mysql, query, strlen(query)))
    if(mysql_query(&mysql, query)!=0) // success
    {
        printf( "Failed to find any records and caused an error:%s\n", mysql_error(&mysql));
    }
    else {
        printf("%ld Record Found\n",(long) mysql_affected_rows(&mysql));
        result = mysql_store_result(&mysql);
        if (result)  // there are rows
        {
            num_fields = mysql_num_fields(result);
            while ((row = mysql_fetch_row(result))) 
            {
                unsigned long *lengths = mysql_fetch_lengths(result);
                for(i = 0; i < num_fields; i++) 
                {
                    printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL"); 
                }
                printf("\n");
            }
            mysql_free_result(result);
        }
        else  // mysql_store_result() returned nothing
        {
            if(mysql_field_count(&mysql) > 0)
            // mysql_store_result() should have returned data
            {
                printf( "Error getting records: %s\n", mysql_error(&mysql));
            }
        }
    }
    mysql_close(&mysql);
}
