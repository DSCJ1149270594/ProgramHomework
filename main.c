#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 查验身份证号码
int validateIDCard(const char* idCard) {
    int weights[17] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };  // 对身份证号码前17位数字求加权和的权重
    char checkCodes[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };  // 校验码M的值
    int sum = 0;
    int i = 0;
    for (i = 0; i < 17; i++) {
        sum += (idCard[i] - '0') * weights[i];  // 计算加权和
    }

    int index = sum % 11;  // 取模得到值Z
    char checkCode = checkCodes[index];  // 获取Z对应的校验码M

    return (checkCode == idCard[17]);  // 返回校验结果
}

int main() {
    char** idCards = NULL;  // 用于存储身份证号码的指针数组
    int numIDCards = 0;
    int maxIDCards = 10000;  // 最大输入身份证号码的数量
    int len = 0; // 验证身份证号码长度
    int i = 0;
    // 动态分配内存
    idCards = (char**)malloc(maxIDCards * sizeof(char*));
    if (idCards == NULL) {  //  检验内存是否分配成功
        printf("内存分配失败\n");
        return 1;
    }

    // 用户逐个输入身份证号码
    printf("请输入身份证号码（输入 'q' 或 'Q' 完成号码的输入）：\n");
    while (numIDCards < maxIDCards) {
        printf("身份证号码 %d：", numIDCards + 1);

        // 动态分配内存来存储每个身份证号码
        idCards[numIDCards] = (char*)malloc(20 * sizeof(char));  // 身份证号码长度为18位，最后一位为'\0'
        if (idCards[numIDCards] == NULL) {  //  检验内存是否分配成功
            printf("内存分配失败\n");
            return 1;
        }

        // 使用 fgets 安全地读取用户输入的身份证号码
        if (fgets(idCards[numIDCards], 20, stdin) == NULL) {
            printf("读取输入失败\n");
            return 1;
        }

        // 去除输入中的换行符
        idCards[numIDCards][strcspn(idCards[numIDCards], "\n")] = '\0';
        len = strlen(idCards[numIDCards]);
        if (idCards[numIDCards][0] == 'q' || idCards[numIDCards][0] == 'Q') {
            break;  // 用户输入 'q' 结束输入
        }
        if (len != 18) {
            printf("身份证号码长度( %d位 )不正确，请重新输入\n", len);
            //free(idCards[numIDCards]);
            continue;
        }
        for(i=0;i<len;i++){
            if (!(idCards[numIDCards][i] >= '0' && idCards[numIDCards][i] <='9' || idCards[numIDCards][i] == 'X')) {
				printf("身份证号码包含不合法字符，请重新输入\n");
				//free(idCards[numIDCards]);
				break;
			}
        
        }


        numIDCards++;
    }
    if(numIDCards == 0){
		printf("未输入任何身份证号码！\n");
        // 释放动态分配的内存
        for (i = 0; i < numIDCards; i++) {
            free(idCards[i]);
        }
        free(idCards);
        printf("\n请按回车键退出该程序。\n");
        getchar();  // 等待用户按下回车键退出程序
		return 1;
	}
    printf("在输入的所有身份证号码中，");
    _Bool flag = true;
    for (i = 0; i < numIDCards; i++) {
        if (!validateIDCard(idCards[i])) {
            flag = false;
            break;
        }
    }
    if (flag) {
        printf("所有身份证号码均有效。");
    }else {
        printf("无效身份证号码如下：\n");
    }

    // 判断并输出所有无效身份证号码
    for (i = 0; i < numIDCards; i++) {
        if (!validateIDCard(idCards[i])) {
            printf("%s\n", idCards[i]);
        }
    }

    // 释放动态分配的内存
    for (i = 0; i < numIDCards; i++) {
        free(idCards[i]);
    }
    free(idCards);

    printf("\n请按回车键退出该程序。\n");
    getchar();  // 等待用户按下回车键退出程序

    return 0;
}