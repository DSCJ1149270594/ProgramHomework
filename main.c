#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// �������֤����
int validateIDCard(const char* idCard) {
    int weights[17] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };  // �����֤����ǰ17λ�������Ȩ�͵�Ȩ��
    char checkCodes[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };  // У����M��ֵ
    int sum = 0;
    int i = 0;
    for (i = 0; i < 17; i++) {
        sum += (idCard[i] - '0') * weights[i];  // �����Ȩ��
    }

    int index = sum % 11;  // ȡģ�õ�ֵZ
    char checkCode = checkCodes[index];  // ��ȡZ��Ӧ��У����M

    return (checkCode == idCard[17]);  // ����У����
}

int main() {
    char** idCards = NULL;  // ���ڴ洢���֤�����ָ������
    int numIDCards = 0;
    int maxIDCards = 10000;  // ����������֤���������
    int len = 0; // ��֤���֤���볤��
    int i = 0;
    // ��̬�����ڴ�
    idCards = (char**)malloc(maxIDCards * sizeof(char*));
    if (idCards == NULL) {  //  �����ڴ��Ƿ����ɹ�
        printf("�ڴ����ʧ��\n");
        return 1;
    }

    // �û�����������֤����
    printf("���������֤���루���� 'q' �� 'Q' ��ɺ�������룩��\n");
    while (numIDCards < maxIDCards) {
        printf("���֤���� %d��", numIDCards + 1);

        // ��̬�����ڴ����洢ÿ�����֤����
        idCards[numIDCards] = (char*)malloc(20 * sizeof(char));  // ���֤���볤��Ϊ18λ�����һλΪ'\0'
        if (idCards[numIDCards] == NULL) {  //  �����ڴ��Ƿ����ɹ�
            printf("�ڴ����ʧ��\n");
            return 1;
        }

        // ʹ�� fgets ��ȫ�ض�ȡ�û���������֤����
        if (fgets(idCards[numIDCards], 20, stdin) == NULL) {
            printf("��ȡ����ʧ��\n");
            return 1;
        }

        // ȥ�������еĻ��з�
        idCards[numIDCards][strcspn(idCards[numIDCards], "\n")] = '\0';
        len = strlen(idCards[numIDCards]);
        if (idCards[numIDCards][0] == 'q' || idCards[numIDCards][0] == 'Q') {
            break;  // �û����� 'q' ��������
        }
        if (len != 18) {
            printf("���֤���볤��( %dλ )����ȷ������������\n", len);
            //free(idCards[numIDCards]);
            continue;
        }
        for(i=0;i<len;i++){
            if (!(idCards[numIDCards][i] >= '0' && idCards[numIDCards][i] <='9' || idCards[numIDCards][i] == 'X')) {
				printf("���֤����������Ϸ��ַ�������������\n");
				//free(idCards[numIDCards]);
				break;
			}
        
        }


        numIDCards++;
    }
    if(numIDCards == 0){
		printf("δ�����κ����֤���룡\n");
        // �ͷŶ�̬������ڴ�
        for (i = 0; i < numIDCards; i++) {
            free(idCards[i]);
        }
        free(idCards);
        printf("\n�밴�س����˳��ó���\n");
        getchar();  // �ȴ��û����»س����˳�����
		return 1;
	}
    printf("��������������֤�����У�");
    _Bool flag = true;
    for (i = 0; i < numIDCards; i++) {
        if (!validateIDCard(idCards[i])) {
            flag = false;
            break;
        }
    }
    if (flag) {
        printf("�������֤�������Ч��");
    }else {
        printf("��Ч���֤�������£�\n");
    }

    // �жϲ����������Ч���֤����
    for (i = 0; i < numIDCards; i++) {
        if (!validateIDCard(idCards[i])) {
            printf("%s\n", idCards[i]);
        }
    }

    // �ͷŶ�̬������ڴ�
    for (i = 0; i < numIDCards; i++) {
        free(idCards[i]);
    }
    free(idCards);

    printf("\n�밴�س����˳��ó���\n");
    getchar();  // �ȴ��û����»س����˳�����

    return 0;
}