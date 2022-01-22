/***********************************************************************/
/*                          HW# 2-1. GL Modeling                        */
/*  작성자 : 차현아                              날짜 : 2021년 9월 24일 */
/*                                                                      */
/* 문제 정의 : 2D Primitive 구현하기                                    */
/*                - - - - - - -                                         */
/* 기능 : 1.Points / 2.Lines / 3. LineStrip / 4. LineLoop               */
/*        5. Polygons / 6. Triangles / 7. TriangleStrip                 */
/*        8. TriangleFan / 9.Quads / 10. QuadStrip                      */
/***********************************************************************/
#include <GL/glut.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); // 색상버퍼지우기
    glColor3f(1.0, 0.0, 0.0); // 빨간색으로 그리기
    glPointSize(4.5); // 점의 크기 지정 - 눈에 잘 띄게 하기 위해 크기 조정
    glLineWidth(1.5); // 라인의 두께 지정
    glShadeModel(GL_FLAT); // 단색으로 칠하기 -> 디폴트 설정값이 GL_SMOOTH이므로 GL_FLAT으로 설정해주었음.
                           // -> 컬러로 나뉘는 영역들을 구분할 것이기 때문
                           // GL_SMOOTH로 되어있으면 색으로 영역을 구분하기가 어려움

    // 1. Points - 독립적인 점 찍기
    //glBegin(GL_POINTS); // 6각형의 꼭짓점들을 구현
    //glVertex3f(-0.5, -1.0, 0.0);
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 2. Lines - 두개의 정점들을 이은 선분
    //glBegin(GL_LINES);
    //glVertex3f(-0.5, -1.0, 0.0); // 찍힌 차례대로 2개씩 짝지어 연결됨
    //glVertex3f(0.5, -1.0, 0.0);

    //glVertex3f(1.0, 0.0, 0.0); // 하나의 선분
    //glVertex3f(0.5, 1.0, 0.0);

    //glVertex3f(-0.5, 1.0, 0.0); // 하나의 선분
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 3, LineStrip - 연결된 선분
    //glBegin(GL_LINE_STRIP);
    //glVertex3f(-0.5, -1.0, 0.0); // 차례대로 연결됨 - 처음 vertex와 마지막 vertex는 연결되지않음
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 4. LineLoop - (시작점과 끝점 포함) 연결된 선분
    //glBegin(GL_LINE_LOOP);
    //glVertex3f(-0.5, -1.0, 0.0); // 차례대로 연결짓고, 마지막점과 첫점도 연결됨
    //glVertex3f(0.5, -1.0, 0.0);  // -> 6각형 형태로 그려짐
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 5. Polygons - 다각형 
    //glBegin(GL_POLYGON);
    //glVertex3f(-0.5, -1.0, 0.0); // 차례대로 연결하여 다각형을 만듦
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 6. Triangles - vertex를 3개씩 연결한 삼각형
    //glBegin(GL_TRIANGLES);
    //glVertex3f(-0.5, -1.0, 0.0); // 총 두개의 삼각형이 만들어짐
    //glVertex3f(0.5, -1.0, 0.0);
    //glVertex3f(1.0, 0.0, 0.0);
    //glVertex3f(0.5, 1.0, 0.0);
    //glVertex3f(-0.5, 1.0, 0.0);
    //glVertex3f(-1.0, 0.0, 0.0);
    //glEnd();

    // 7. TriangleStrip - 연결되는 삼각형
    //glBegin(GL_TRIANGLE_STRIP); // 점들을 순서대로 연결하여 이어지는 삼각형이 만들어짐
    //glVertex3f(1.8, -1.5, 0.0); // -> vertex 7개로 5개의 삼각형이 만들어짐
    //glVertex3f(1.4, 1.3, 0.0);  // 첫 삼각형은 레드로 그려짐
    //glVertex3f(0.9, -0.9, 0.0);
    //// 삼각형들을 서로다른 색으로 구분하였음
    //glColor3f(0.0, 1.0, 0.0); // 그린 - 두번째 삼각형
    //glVertex3f(0.0, 1.9, 0.0);
    //glColor3f(1.0, 0.0, 1.0); // 핑크 - 세번째 삼각형
    //glVertex3f(-0.6, -1.2, 0.0);
    //glColor3f(0.0, 0.0, 1.0); // 블루 - 네번째 삼각형
    //glVertex3f(-1.2, 1.5, 0.0);
    //glColor3f(0.0, 0.0, 0.0); // 검정색 - 다섯번째 삼각형
    //glVertex3f(-1.8, -1.0, 0.0);
    //glEnd();

    //8. TriangleFan - 하나의 중심 vertex를 공유하는 삼각형
    //glBegin(GL_TRIANGLE_FAN); // 점이 찍히는 순서대로 연결됨
    //glVertex3f(-1.8,-1.8, 0.0); // 레드 - 첫번째 삼각형
    //glVertex3f(1.7,-1.5,0.0);
    //glVertex3f(1.5, -0.5,0.0);
    //glColor3f(0.0, 0.0, 1.0); // 블루 - 두번째 삼각형
    //glVertex3f(1.1, 0.4,0.0);
    //glColor3f(1.0, 1.0, 0.0); // 노랑 - 세번째 삼각형
    //glVertex3f(0.8, 1.0,0.0);
    //glColor3f(0.0, 0.0, 0.0); // 블랙 - 마지막 삼각형
    //glVertex3f(0.5, 1.5,0.0);
    //glEnd();

    //9. Quads - vertex를 4개씩 연결하여 사각형 그리기 
    //glBegin(GL_QUADS); // 가시부피에 들어오도록, 볼록사각형이 그려지도록 적절히 vertex위치 선정하였음
    //glVertex3f(1.5, -1.2, 0.0); // 레드 - 첫번째 사각형 
    //glVertex3f(1.5,0.6,0.0);
    //glVertex3f(0.5, 0.9,0.0);
    //glVertex3f(0.7, -1.6, 0.0);
    //glColor3f(0.0, 0.0, 0.0); // 블랙 - 두번째 사각형
    //glVertex3f(-0.6, -0.4, 0.0);
    //glVertex3f(-1.0, 0.5, 0.0);
    //glVertex3f(-1.8, 0.6, 0.0);
    //glVertex3f(-0.9, -1.1, 0.0);
    //glEnd();

    // 10. QuadStrip - 연결되는 사각형 * vertex 가 지그재그 형태로 찍혀야 오목한 형태가 아닌 제대로 된 볼록사각형이 만들어짐.
    glBegin(GL_QUAD_STRIP); // -> vertex를 차례대로 연결했을 때, 사각형의 선분끼리 이어지도록 연결되면 안됨 -> 차례대로 연결했을때 사각형이 만들어지면 안됨
    glVertex3f(1.5, -1.2, 0.0); // 레드 -> 첫번째 사각형
    glVertex3f(1.5,0.6,0.0);
    glVertex3f(0.7, -1.6, 0.0); 
    glVertex3f(0.5, 0.9,0.0);
    glColor3f(0.0, 0.0, 0.0); // 블랙 -> 중간 사각형
    glVertex3f(-0.6, -0.4, 0.0);
    glVertex3f(-1.0, 0.5, 0.0);
    glVertex3f(-0.9, -1.1, 0.0); 
    glColor3f(0.0, 0.0, 1.0); // 블루 -> 마지막 사각형
    glVertex3f(-1.8, 0.6, 0.0);
    glVertex3f(-0.9, -1.1, 0.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500); // 윈도우 사이즈
    glutInitWindowPosition(20, 20); // 윈도우 위치
    glutCreateWindow("Graphics Primitives");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0); // 가시부피를 고려하여 vertex 위치를 설정하였음
    glutDisplayFunc(MyDisplay); // 콜백함수 등록

    glutMainLoop();
    return 0;
}