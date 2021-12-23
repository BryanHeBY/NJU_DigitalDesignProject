#include <myterm.h>

enum {
  TK_HEX_NUM, TK_DEC_NUM,
  TK_L_PARE, TK_R_PARE,
  TK_ADD, TK_SUB, TK_MUL, TK_DIV,
  TK_ALL_END

};

#define EVAL_ERROR(fmt, ...) printf(ASNI_FMT("[expr.c:%d %s] " fmt, ASNI_FG_RED), __LINE__, __func__ ,## __VA_ARGS__)

static inline int32_t OP_PRI(uint32_t TK_TYPE){
  switch (TK_TYPE)
  {
    case TK_ADD: case TK_SUB:
      return 1;
    case TK_MUL: case TK_DIV:
      return 2;
    default:
      return 0;
  }
}

typedef struct token {
  int type;
  char *str;
} Token;

#define TK_BF_L 32

static Token tokens[TK_BF_L];
static int nr_token = 0;

static bool make_token(char *line) {
  nr_token = 0;

  int len = strlen(line);

  for(int i = 0; i < len;){
      switch (line[i]){
        case ' ':
            line[i] = '\n';
            i++;
            break;
        case '(':
            tokens[nr_token] = (Token){.type=TK_L_PARE, .str=NULL};
            line[i] = '\0';
            nr_token++;
            i++;
            break;
        case ')':
            tokens[nr_token] = (Token){.type=TK_R_PARE, .str=NULL};
            line[i] = '\0';
            nr_token++;
            i++;
            break;
        case '+':
            tokens[nr_token] = (Token){.type=TK_ADD, .str=NULL};
            line[i] = '\0';
            nr_token++;
            i++;
            break;
        case '-':
            tokens[nr_token] = (Token){.type=TK_SUB, .str=NULL};
            line[i] = '\0';
            nr_token++;
            i++;
            break;
        case '*':
            tokens[nr_token] = (Token){.type=TK_MUL, .str=NULL};
            line[i] = '\0';
            nr_token++;
            i++;
            break;
        case '/':
            tokens[nr_token] = (Token){.type=TK_DIV, .str=NULL};
            line[i] = '\0';
            nr_token++;
            i++;
            break;
        default:
            if(line[i] == '0' && line[i+1] == 'x'){
                tokens[nr_token] = (Token){.type=TK_HEX_NUM, .str=line+i};
                nr_token++;
                i += 2;
                while((line[i] >= '0' && line[i] <= '9') || (line[i] >= 'a' && line[i] <= 'f'))i++;
            }
            else if(line[i] >= '0' && line[i] <= '9'){
                tokens[nr_token] = (Token){.type=TK_DEC_NUM, .str=line+i};
                nr_token++;
                while(line[i] >= '0' && line[i] <= '9')i++;
            }
            else {
                printf("Unknown token!\n");
                return false;
            }
            break;
      }
  }

  tokens[nr_token++].type = TK_ALL_END;

  return true;
}


static int32_t tokens_index;                                            //队列队首位置
#define NOW_TK tokens[tokens_index]                                    //目前队首
#define POP_TK() tokens_index++                                        //队首出队
static int32_t get_atom(bool *success);                                 //获得原子表达式
static int32_t get_expr(int32_t op_pri_min, bool *success);              //获得一般表达式

static int32_t get_atom(bool *success){
  int32_t res;
  switch (NOW_TK.type) //判断当前token类型
  {
    case TK_DEC_NUM:   //十进制数，直接返回
      res = atoi(NOW_TK.str);
      POP_TK();        //队首出队
      break;
    case TK_HEX_NUM:   //十六进制数，直接返回
      res = htoi(NOW_TK.str);
      POP_TK();
      break;
    case TK_ADD:      //正号，返回后一个原子表达式的值
      POP_TK();
      res = get_atom(success);
      break;
    case TK_SUB:      //负号，返回后一个原子表达式的相反数
      POP_TK();
      res = -get_atom(success);
      break;
    case TK_L_PARE:  //左括号，计算
      POP_TK();  //左括号出队
      res = get_expr(0, success);
      if(NOW_TK.type != TK_R_PARE){  //判断结束符是不是右括号
        EVAL_ERROR("Right parenthesis doesn't match.\n");
        *success = false;
        return 0;
      }
      POP_TK();  //右括号出队
      break;
    default:
      *success = false;
      EVAL_ERROR("Unexpected begin token type: %d\n", NOW_TK.type);
      return 0;
  }
  return res;
}

#define IS_END_TOKEN(type) (type == TK_R_PARE || type == TK_ALL_END)   //结束符（右括号或整体结束）
#define IS_OP_TOKEN(type) (type >= TK_ADD && type <= TK_DIV)            //双目运算符判断

static int32_t get_expr(int32_t op_pri_min, bool *success){
  int32_t res = get_atom(success);  //先获得一个做操作数（或原子表达式）
  if(!*success){
    return 0;
  }
  while(true){
    uint32_t op_type = NOW_TK.type; //当前要处理的运算符优先级
    if(IS_END_TOKEN(op_type))break; //若当前token是右括号或整体结束符号
    if(!IS_OP_TOKEN(op_type)){
      EVAL_ERROR("Unexpect operator token type: %d.\n",NOW_TK.type);
      *success = false;
      return 0;
    }
    if(OP_PRI(op_type) < op_pri_min)break; //若操作符优先级小于整体最低优先级，就退出
    POP_TK(); //操作符出队
    int32_t src = get_expr(OP_PRI(op_type) + 1, success);  //右操作数优先级要求严格大于运算符优先级
    switch (op_type) //根据操作符类型进行操作
    {
      case TK_ADD: res = res + src;  break;
      case TK_SUB: res = res - src;  break;
      case TK_MUL: res = res * src;  break;
      case TK_DIV: 
        if(!src){
          EVAL_ERROR("Devided by zero error!\n");
          *success = false;
          return 0;
        }
        res = res / src;  
        break;
    }
  }
  
  return res;
}

int32_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  *success = true;
  tokens_index = 0;
  int32_t res = get_expr(0, success);
  if(NOW_TK.type != TK_ALL_END){
    *success = false;
    EVAL_ERROR("Unexpected end token type: %d\n", NOW_TK.type);
  }
  if(!*success)return 0;
  return res;
}

int exe_eval(int argc, char *argv[]){
    char *line = readline();
    bool success = true;
    int ret = expr(line, &success);
    if(!success){
        printf("Eval error!\n");
        return 255;
    }
    printf("   =  %d\n", ret);
    return 0;
}
