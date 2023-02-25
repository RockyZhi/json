//һ����д�ĵݹ��½�������
//���� JSON �﷨�ر�򵥣����ǲ���Ҫд�ִ�����ֻ�����һ���ַ��������֪�������������͵�ֵ
//ʵ�֣����������� JSON ��䣬�����հף�����һ���ַ�

#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

// JSON�ı�
typedef struct {
    const char* json;
}lept_context;

// ���˵��հף�whitespace��
static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

//
static int lept_parse_null(lept_context* c, lept_value* v) {
    // ���ж��ԣ���ǰ�ַ�������n������������һ�ַ�
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

// ����û�������� ws �� LEPT_PARSE_ROOT_NOT_SINGULAR 
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    //�� lept_parse() ʧ�ܣ���� v ��Ϊ null ����
    //���������Ȱ�����Ϊ null���� lept_parse_value() д����������ĸ�ֵ��
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    return lept_parse_value(&c, v);
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
