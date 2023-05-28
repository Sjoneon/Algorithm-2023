#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct PriorityQueue {
    Node* node;
    struct PriorityQueue* next;
} PriorityQueue;

Node* createNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

PriorityQueue* createQueueNode(Node* node) {
    PriorityQueue* queueNode = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queueNode->node = node;
    queueNode->next = NULL;
    return queueNode;
}

void enqueue(PriorityQueue** queue, Node* node) {
    PriorityQueue* queueNode = createQueueNode(node);
    if (*queue == NULL || node->frequency < (*queue)->node->frequency) {
        queueNode->next = *queue;
        *queue = queueNode;
    }
    else {
        PriorityQueue* current = *queue;
        while (current->next != NULL && current->next->node->frequency <= node->frequency) {
            current = current->next;
        }
        queueNode->next = current->next;
        current->next = queueNode;
    }
}

Node* dequeue(PriorityQueue** queue) {
    if (*queue == NULL) {
        return NULL;
    }
    Node* node = (*queue)->node;
    PriorityQueue* temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return node;
}

Node* buildHuffmanTree(int frequencies[], char characters[], int n) {
    PriorityQueue* queue = NULL;
    for (int i = 0; i < n; i++) {
        Node* node = createNode(characters[i], frequencies[i]);
        enqueue(&queue, node);
    }

    while (queue != NULL && queue->next != NULL) {
        Node* left = dequeue(&queue);
        Node* right = dequeue(&queue);

        Node* parent = createNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        enqueue(&queue, parent);
    }

    Node* root = dequeue(&queue);
    free(queue);
    return root;
}

void findCharacterCode(Node* root, char character, char code[], int depth, char** codes) {
    if (root == NULL) {
        return;
    }

    if (root->character == character) {
        code[depth] = '\0';
        *codes = strdup(code);
        return;
    }

    code[depth] = '0';
    findCharacterCode(root->left, character, code, depth + 1, codes);

    code[depth] = '1';
    findCharacterCode(root->right, character, code, depth + 1, codes);
}

void buildCharacterCodes(Node* root, char* characters, char* codes[], int n) {
    char code[256];
    for (int i = 0; i < n; i++) {
        findCharacterCode(root, characters[i], code, 0, &codes[i]);
    }
}

char* convertStringToBits(char* inputString, char** codes, int n) {
    int length = strlen(inputString);
    char* bits = (char*)malloc((length * 8 + 1) * sizeof(char));
    int index = 0;

    for (int i = 0; i < length; i++) {
        char* code = codes[(int)inputString[i]];
        int codeLength = strlen(code);
        for (int j = 0; j < codeLength; j++) {
            bits[index++] = code[j];
        }
    }

    bits[index] = '\0';
    return bits;
}

void writeBitsToFile(FILE* outputFile, char* bits) {
    int length = strlen(bits);
    int padding = 8 - (length % 8);
    if (padding == 8) {
        padding = 0;
    }

    fwrite(&padding, sizeof(unsigned char), 1, outputFile);

    for (int i = 0; i < length; i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8; j++) {
            if (bits[i + j] == '1') {
                byte |= (1 << (7 - j));
            }
        }
        fwrite(&byte, sizeof(unsigned char), 1, outputFile);
    }
}

int compressHuffman(FILE* inputFile, FILE* outputFile, Node* root, char* characters, char** codes, int n) {
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char* inputString = (char*)malloc((fileSize + 1) * sizeof(char));
    fread(inputString, sizeof(char), fileSize, inputFile);
    inputString[fileSize] = '\0';

    char* bits = convertStringToBits(inputString, codes, n);
    int totalBits = strlen(bits);

    writeBitsToFile(outputFile, bits);

    free(inputString);
    free(bits);

    return totalBits;
}


void decompressHuffman(FILE* inputFile, FILE* outputFile, Node* root, int totalBits) {
    Node* currentNode = root;
    int bitCount = 0;
    unsigned char byte;

    while (bitCount < totalBits) {
        if (bitCount % 8 == 0) {
            byte = fgetc(inputFile);
        }

        if ((byte >> (7 - bitCount % 8)) & 1) {
            currentNode = currentNode->right;
        }
        else {
            currentNode = currentNode->left;
        }

        if (currentNode->left == NULL && currentNode->right == NULL) {
            fputc(currentNode->character, outputFile);
            currentNode = root;
        }

        bitCount++;
    }
}

int main() {
    char inputFileName[] = "input.txt";
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("입력 파일을 열 수 없습니다.\n");
        return 1;
    }

    int frequencies[256] = { 0 };
    char character;
    while ((character = fgetc(inputFile)) != EOF) {
        frequencies[(int)character]++;
    }
    fclose(inputFile);

    int numCharacters = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            numCharacters++;
        }
    }
    char* characters = (char*)malloc(numCharacters * sizeof(char));
    int* nonZeroFrequencies = (int*)malloc(numCharacters * sizeof(int));
    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            characters[index] = (char)i;
            nonZeroFrequencies[index] = frequencies[i];
            index++;
        }
    }

    Node* huffmanTree = buildHuffmanTree(nonZeroFrequencies, characters, numCharacters);

    char* codes[256] = { NULL };
    buildCharacterCodes(huffmanTree, characters, codes, numCharacters);

    FILE* outputFile = fopen("output.huf", "wb");
    if (outputFile == NULL) {
        printf("출력 파일을 열 수 없습니다.\n");
        return 1;
    }

    int totalBits = compressHuffman(inputFile, outputFile, huffmanTree, characters, codes, numCharacters);
    fclose(outputFile);

    FILE* statsFile = fopen("stats.txt", "w");
    if (statsFile == NULL) {
        printf("빈도수 파일을 열 수 없습니다.\n");
        return 1;
    }

    for (int i = 0; i < numCharacters; i++) {
        fprintf(statsFile, "%c\t%d\n", characters[i], nonZeroFrequencies[i]);
    }
    fclose(statsFile);

    FILE* compressedFile = fopen("output.huf", "rb");
    if (compressedFile == NULL) {
        printf("압축 파일을 열 수 없습니다.\n");
        return 1;
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("압축 해제 파일을 열 수 없습니다.\n");
        return 1;
    }

    decompressHuffman(compressedFile, outputFile, huffmanTree, totalBits);
    fclose(compressedFile);
    fclose(outputFile);

    // 메모리 해제
    free(characters);
    free(nonZeroFrequencies);
    for (int i = 0; i < numCharacters; i++) {
        free(codes[i]);
    }

    return 0;
}