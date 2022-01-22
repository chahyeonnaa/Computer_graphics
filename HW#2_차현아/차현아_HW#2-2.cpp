/***********************************************************************/
/*                 HW#2-2. GLU Modeling                                */
/*  작성자 : 차현아                           날짜 : 2021년 9월 24일   */
/*                                                                     */
/* 문제 정의 : 3D Primitive 구현하기                                   */
/*                                                                     */
/* 기능 : Sphere, Cylinder, Disk, PartialDisk 구현하기                 */
/*                                                                     */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>

GLUquadricObj* qobj = gluNewQuadric(); // 새로운 Quadric 생성
int list[4]; // Display List를 위한 배열 -> 4개의 아이디를 할당받기 위한 공간(정수 ID에 의해 식별)

void MyInit(void) { // 코드 4-5
    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat model_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}
void MyCreateList()
{
    // 아이디 할당
    list[0] = glGenLists(4); // 실린더 아이디를 list[0]에 할당
    list[1] = list[0] + 1; // 구 아이디 할당
    list[2] = list[0] + 2; // 디스크 아이디 할당
    list[3] = list[0] + 3; // 부분디스크 아이디 할당

    // 실린더
    glNewList(list[0], GL_COMPILE); // Display List를 생성하기 위한 함수_list[0]에 기록 시작
    gluQuadricDrawStyle(qobj, GLU_POINT); // 점으로만 그려짐
    gluQuadricNormals(qobj, GLU_SMOOTH); // 모서리를 부드럽게 보이도록 하기 위해 법선벡터 생성
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 방향 설정(바깥쪽)
    gluQuadricTexture(qobj, GL_FALSE); // 텍스쳐 좌표를 생성하지않음
    glRotatef(200, 1.0, 1.0, 1.0); // 입체감을 더하기 위해 (1,1,1)을 축으로 200도 회전시킴
    gluCylinder(qobj, 1.5, 0.0, 1.6, 20, 20); // 반지름이 1.5 이고, 높이가 1.6인 실린더
    glEndList(); // Display List의 끝을 표시하는 함수_list[0]에 들어갈 정보 입력 완료

    // 구
    glNewList(list[1], GL_COMPILE);// Display List를 생성하기 위한 함수_list[1]에 기록 시작
    gluQuadricDrawStyle(qobj, GLU_LINE); // 선으로만 그려짐
    gluQuadricNormals(qobj, GLU_SMOOTH); // 모서리를 부드럽게 보이도록 하기 위해 법선벡터 생성
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 방향 설정(바깥쪽)
    gluQuadricTexture(qobj, GL_FALSE); // 텍스쳐 좌표를 생성하지않음
    gluSphere(qobj, 1.5, 50, 50); // 반지름이 1.5인 구(최대한 원처럼 보이기 위해 50각형으로 구성)
    glEndList(); // Display List의 끝을 표시하는 함수_list[1]에 들어갈 정보 입력 완료

    // 디스크
    glNewList(list[2], GL_COMPILE); // Display List를 생성하기 위한 함수_list[2]에 기록 시작
    gluQuadricDrawStyle(qobj, GLU_FILL); // solid 형태로 그려짐(색으로 가득 채워짐)
    gluQuadricNormals(qobj, GLU_SMOOTH); // 모서리를 부드럽게 보이도록 하기 위해 법선벡터 생성
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 방향 설정(바깥쪽)
    gluQuadricTexture(qobj, GL_FALSE); // 텍스쳐 좌표를 생성하지않음
    glRotatef(200, 1.0, 1.0, 1.0); // (1, 1, 1)을 축으로 200도 회전시킴
    gluDisk(qobj, 0.5, 2.0, 20, 5); // 안쪽반지름 = 0.5 , 바깥 반지름이 2인 디스크
    glEndList(); // Display List의 끝을 표시하는 함수_list[2]에 들어갈 정보 입력 완료

    // 부분디스크
    glNewList(list[3], GL_COMPILE); // Display List를 생성하기 위한 함수_list[3]에 기록 시작
    gluQuadricDrawStyle(qobj, GLU_SILHOUETTE); // 외부 모서리만 그려짐
    gluQuadricNormals(qobj, GLU_SMOOTH); // 모서리를 부드럽게 보이도록 하기 위해 법선벡터 생성
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 방향 설정(바깥쪽)
    gluQuadricTexture(qobj, GL_FALSE); // 텍스쳐 좌표를 생성하지않음
    gluPartialDisk(qobj, 0.5, 1.0, 26, 13, 80, 280); // 안쪽 반지름이 0.5, 바깥 반지름이 1, 원호 시작각도 80, sweep각도가 280인 부분디스크
    glEndList(); // Display List의 끝을 표시하는 함수_list[3]에 들어갈 정보 입력 완료


}
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_FLAT);
    glPointSize(5); // 점의 크기 지정

    // Display List를 실행하기 위한 함수
    glCallList(list[0]); // 실린더
    //glCallList(list[1]); // 구
    //glCallList(list[2]); // 디스크
    //glCallList(list[3]); // 부분디스크

    glutSwapBuffers(); // 전면버퍼와 후면버퍼를 swap, 이것의 위치를 glEndList() 이전에 두었다가 검은화면 오류가 발생함.

    glFlush();

}

void MyReshape(int NewWidth, int NewHeight) // 왜곡문제 해결함수(매개변수는 os가 알려주는 조정된 새로운 윈도우의 크기)
{
    glViewport(0, 0, NewWidth, NewHeight); // 조정된 윈도우 전체를 뷰폿으로 지정
    GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; // 조정된 비율을 알기위해 초기 윈도우 크기를 새로운 값들로 나누어줌
    GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; // -> 위에서 결정된 비율만큼 가시부피를 바꾸어야함
    glMatrixMode(GL_PROJECTION); // 가시부피를 바꿔주기 위해 투영행렬을 쓰겠다고 지정
    glLoadIdentity();
    glOrtho(-2.0 * Widthfactor, 2.0 * Widthfactor, -2.0 * Heightfactor, 2.0 * Heightfactor, -10.0, 10.0);
    // depth는 그대로두고, 조정된 크기의 비율만큼 기존 값들에 곱해줌 -> 가시부피 조정
    // left, right, bottom, top, -near, -far순서로 가시부피 설정
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 더블 버퍼사용_ glutSwapBuffers 위치와 연관
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Primitives");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    MyCreateList();

    glutMainLoop();
    return 0;
}