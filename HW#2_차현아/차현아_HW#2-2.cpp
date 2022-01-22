/***********************************************************************/
/*                 HW#2-2. GLU Modeling                                */
/*  �ۼ��� : ������                           ��¥ : 2021�� 9�� 24��   */
/*                                                                     */
/* ���� ���� : 3D Primitive �����ϱ�                                   */
/*                                                                     */
/* ��� : Sphere, Cylinder, Disk, PartialDisk �����ϱ�                 */
/*                                                                     */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>

GLUquadricObj* qobj = gluNewQuadric(); // ���ο� Quadric ����
int list[4]; // Display List�� ���� �迭 -> 4���� ���̵� �Ҵ�ޱ� ���� ����(���� ID�� ���� �ĺ�)

void MyInit(void) { // �ڵ� 4-5
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
    // ���̵� �Ҵ�
    list[0] = glGenLists(4); // �Ǹ��� ���̵� list[0]�� �Ҵ�
    list[1] = list[0] + 1; // �� ���̵� �Ҵ�
    list[2] = list[0] + 2; // ��ũ ���̵� �Ҵ�
    list[3] = list[0] + 3; // �κе�ũ ���̵� �Ҵ�

    // �Ǹ���
    glNewList(list[0], GL_COMPILE); // Display List�� �����ϱ� ���� �Լ�_list[0]�� ��� ����
    gluQuadricDrawStyle(qobj, GLU_POINT); // �����θ� �׷���
    gluQuadricNormals(qobj, GLU_SMOOTH); // �𼭸��� �ε巴�� ���̵��� �ϱ� ���� �������� ����
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // �������� ���� ����(�ٱ���)
    gluQuadricTexture(qobj, GL_FALSE); // �ؽ��� ��ǥ�� ������������
    glRotatef(200, 1.0, 1.0, 1.0); // ��ü���� ���ϱ� ���� (1,1,1)�� ������ 200�� ȸ����Ŵ
    gluCylinder(qobj, 1.5, 0.0, 1.6, 20, 20); // �������� 1.5 �̰�, ���̰� 1.6�� �Ǹ���
    glEndList(); // Display List�� ���� ǥ���ϴ� �Լ�_list[0]�� �� ���� �Է� �Ϸ�

    // ��
    glNewList(list[1], GL_COMPILE);// Display List�� �����ϱ� ���� �Լ�_list[1]�� ��� ����
    gluQuadricDrawStyle(qobj, GLU_LINE); // �����θ� �׷���
    gluQuadricNormals(qobj, GLU_SMOOTH); // �𼭸��� �ε巴�� ���̵��� �ϱ� ���� �������� ����
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // �������� ���� ����(�ٱ���)
    gluQuadricTexture(qobj, GL_FALSE); // �ؽ��� ��ǥ�� ������������
    gluSphere(qobj, 1.5, 50, 50); // �������� 1.5�� ��(�ִ��� ��ó�� ���̱� ���� 50�������� ����)
    glEndList(); // Display List�� ���� ǥ���ϴ� �Լ�_list[1]�� �� ���� �Է� �Ϸ�

    // ��ũ
    glNewList(list[2], GL_COMPILE); // Display List�� �����ϱ� ���� �Լ�_list[2]�� ��� ����
    gluQuadricDrawStyle(qobj, GLU_FILL); // solid ���·� �׷���(������ ���� ä����)
    gluQuadricNormals(qobj, GLU_SMOOTH); // �𼭸��� �ε巴�� ���̵��� �ϱ� ���� �������� ����
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // �������� ���� ����(�ٱ���)
    gluQuadricTexture(qobj, GL_FALSE); // �ؽ��� ��ǥ�� ������������
    glRotatef(200, 1.0, 1.0, 1.0); // (1, 1, 1)�� ������ 200�� ȸ����Ŵ
    gluDisk(qobj, 0.5, 2.0, 20, 5); // ���ʹ����� = 0.5 , �ٱ� �������� 2�� ��ũ
    glEndList(); // Display List�� ���� ǥ���ϴ� �Լ�_list[2]�� �� ���� �Է� �Ϸ�

    // �κе�ũ
    glNewList(list[3], GL_COMPILE); // Display List�� �����ϱ� ���� �Լ�_list[3]�� ��� ����
    gluQuadricDrawStyle(qobj, GLU_SILHOUETTE); // �ܺ� �𼭸��� �׷���
    gluQuadricNormals(qobj, GLU_SMOOTH); // �𼭸��� �ε巴�� ���̵��� �ϱ� ���� �������� ����
    gluQuadricOrientation(qobj, GLU_OUTSIDE); // �������� ���� ����(�ٱ���)
    gluQuadricTexture(qobj, GL_FALSE); // �ؽ��� ��ǥ�� ������������
    gluPartialDisk(qobj, 0.5, 1.0, 26, 13, 80, 280); // ���� �������� 0.5, �ٱ� �������� 1, ��ȣ ���۰��� 80, sweep������ 280�� �κе�ũ
    glEndList(); // Display List�� ���� ǥ���ϴ� �Լ�_list[3]�� �� ���� �Է� �Ϸ�


}
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_FLAT);
    glPointSize(5); // ���� ũ�� ����

    // Display List�� �����ϱ� ���� �Լ�
    glCallList(list[0]); // �Ǹ���
    //glCallList(list[1]); // ��
    //glCallList(list[2]); // ��ũ
    //glCallList(list[3]); // �κе�ũ

    glutSwapBuffers(); // ������ۿ� �ĸ���۸� swap, �̰��� ��ġ�� glEndList() ������ �ξ��ٰ� ����ȭ�� ������ �߻���.

    glFlush();

}

void MyReshape(int NewWidth, int NewHeight) // �ְ�� �ذ��Լ�(�Ű������� os�� �˷��ִ� ������ ���ο� �������� ũ��)
{
    glViewport(0, 0, NewWidth, NewHeight); // ������ ������ ��ü�� �������� ����
    GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; // ������ ������ �˱����� �ʱ� ������ ũ�⸦ ���ο� ����� ��������
    GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; // -> ������ ������ ������ŭ ���ú��Ǹ� �ٲپ����
    glMatrixMode(GL_PROJECTION); // ���ú��Ǹ� �ٲ��ֱ� ���� ��������� ���ڴٰ� ����
    glLoadIdentity();
    glOrtho(-2.0 * Widthfactor, 2.0 * Widthfactor, -2.0 * Heightfactor, 2.0 * Heightfactor, -10.0, 10.0);
    // depth�� �״�εΰ�, ������ ũ���� ������ŭ ���� ���鿡 ������ -> ���ú��� ����
    // left, right, bottom, top, -near, -far������ ���ú��� ����
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ���� ���ۻ��_ glutSwapBuffers ��ġ�� ����
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