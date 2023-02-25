//一个手写的递归下降解析器
//由于 JSON 语法特别简单，我们不需要写分词器，只需检测第一个字符，便可以知道它是哪种类型的值
//实现：对于完整的 JSON 语句，跳过空白，检测第一个字符

#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

// JSON文本
typedef struct {
    const char* json;
}lept_context;

// 过滤掉空白（whitespace）
static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

//
static int lept_parse_null(lept_context* c, lept_value* v) {
    // 进行断言（当前字符必须是n），并跳到下一字符
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

// 这里没处理最后的 ws 和 LEPT_PARSE_ROOT_NOT_SINGULAR 
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    //若 lept_parse() 失败，会把 v 设为 null 类型
    //所以这里先把它设为 null，让 lept_parse_value() 写入解析出来的根值。
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    return lept_parse_value(&c, v);
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
