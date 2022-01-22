/***********************************************************************/
/*                 HW#8 : ����                                         */
/*  �ۼ��� : ������                           ��¥ : 2021�� 12�� 3��   */
/*                                                                     */
/* ���� ���� : ���ݱ��� ������ ���� ������ �����Ͽ� ��ü �𵨸�        */
/*            �䱸���� -  �� 8���� ������                            */
/* ���� : �޸�ũ��������                                               */
/*     ũ�������� Ʈ���� ���� ������ ����� �����Ͽ����ϴ�.            */
/*     Ʈ������ ���� ���ʸ�Ʈ���� �ް�,�Ʒ����� ������ ��ġ�Ͽ����ϴ�. */
/*     ������ �ؽ��ĸ����� �̿��Ͽ� �������� ���� �Ͽ����ϴ�           */
/*     �ΰ��� ������ Ʈ���� �յڷ� �ٸ���ġ�� ��ġ�Ͽ� �����ϰ� ������ ���߾����ϴ�. */
/*     �޴��ݹ��� �̿��Ͽ� ������ Ȯ���� �� �ֽ��ϴ�.                       */
/*     ������ ������ü�� ������ ����� ������ �ؽ��ĸ����� ��������ü�Դϴ�.*/
/*     Ű���� �ݹ��� ���� �������� �����⸦ ������ �� �ֽ��ϴ�.           */
/*     ���� �������� �ڵ� 10-5�� �����Ͽ����ϴ�.         */
/***********************************************************************/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>  // ��ƿ��Ƽ �Լ��� auxDIBImageLoad()�Լ� ���
#include <GL/glu.h>
#include <stdio.h>

#pragma comment(lib, "glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")

unsigned int MyTextureObject[2]; // �ؽ��� ��ü �̸��Ҵ� ����(�ؽ��� ��ü 2�� -> ������, ����̻���)
AUX_RGBImageRec* pTextureImage[1]; //�ؽ��� ���� ������ ����Ű�� ������(�̹��� �ε�)

int Width, Height;

GLfloat snow = 0.0;
int Stop = 0; // ������ȯ�� ���õ� ����
static bool Case; // ����������

const GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
const GLfloat orange[] = { 1.0, 0.5, 0.0, 1.0 };
const GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
const GLfloat green[] = { 0.2, 1.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 1.0, 1.0, 1.0 };
const GLfloat purple[] = { 0.25, 0.0, 0.5, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat brown[] = { 0.7, 0.25, 0.25, 1.0 };
const GLfloat light_pos[] = { 2.0, 3.0, 4.0, 1.0 };
const GLfloat light_pos2[] = { 10.0, 10.0, -8.0, 1.0 };
// ���� 2�� ���
GLfloat Const = 5.0; // ����- ������������
GLfloat Const2 = 6.0; // ����- ������������
GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0.0 };   // 1D �ؽ��� �������

#define stripeImageWidth    32
GLubyte stripeImage[4 * stripeImageWidth];   // 1D �ؽ��� �迭(����������)

// BMP ������ �ҷ����� �Լ�
AUX_RGBImageRec* LoadBMP(char* szFilename) { // �ؽ��� ������ �迭�� �ٲ��ִ� �Լ�(�ؽ��Ĵ� �迭���·� ����Ǿ����)

	FILE* pFile = NULL;
	if (!szFilename) {
		return NULL;
	}
	fopen_s(&pFile, szFilename, "r");

	// seFilename�� �����ڵ� ��Ʈ������ �ٲٱ�
	int size = strlen(szFilename);
	wchar_t* w_szFilename = new wchar_t[size];

	for (int i = 0; i < size; ++i)  w_szFilename[i] = szFilename[i];
	w_szFilename[size] = NULL;

	if (pFile) {
		fclose(pFile);
		return auxDIBImageLoad(w_szFilename);     //���Ϸκ��� �޸𸮷�	
	}
	return NULL;
}

// �ؽ��� ���� ������ �޸𸮹迭�� �ε��ϰ�, �ؽ��� �޸𸮷� �ø���
int LoadGLTextures(char* szFilePath) { //������ �ε��ϰ� �ؽ��ķ� ��ȯ

	int Status = FALSE;
	glClearColor(0.0, 0.0, 0.0, 0.5);
	memset(pTextureImage, 0, sizeof(void*) * 1); //�̹����� �� �迭(������)�� �η� �ʱ�ȭ

	if (pTextureImage[0] = LoadBMP(szFilePath)) {   //��Ʈ���� �ε��ϰ� ����Ȯ��
		Status = TRUE; // �̹����� �� �ҷ������� true�� ����                             
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]); // ��ü ����
		// �ؽ��ĸ޸𸮿� �ø���
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
		// �ؽ����Ķ���� ���
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ��������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D); // 2D �ؽ��� ���� Ȱ��ȭ
	}
	if (pTextureImage[0]) { // �ؽ��� ���� �޸� �迭�� �����ϸ�                
		if (pTextureImage[0]->data) { // �ؽ��� ���� �޸� �迭 �ȿ� ���� ������ �����ϸ�
			free(pTextureImage[0]->data); //�ؽ��� ������� �ݳ�
		}
		free(pTextureImage[0]); //�ؽ��� �ݳ�
	}
	return Status;
}
void MyDisplay2(void) // ����ü �׸���(��������)
{
	const char* szFilename = "Namu.bmp"; // ���� �ҷ�����
	LoadGLTextures((char*)szFilename); //LoadGLTextures �ȿ��� �ؽ��� �̹����� �迭�� �ҷ�����

	// ����ȿ�� �� glColor �����ϰ�, �ؽ��� ������ ������(GL_REPLACE)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_GEN_S); // 1D �ڵ����� Ȱ��ȭ ����- �Ȳ��ָ� ������ ������ ������
	glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]); // �ؽ��� ��ü ����
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, -1.0f, 3.0f);  //�ո�
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12.0f, 3.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, 3.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(7.0f, -1.0f, -1.0f);  //�޸�
	glTexCoord2f(1.0f, 1.0f); glVertex3f(7.0f, 3.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(12.0f, 3.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(12.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, 3.0f, -1.0f);  //����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 3.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12.0f, 3.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12.0f, 3.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(7.0f, -1.0f, -1.0f);  //�Ʒ���
	glTexCoord2f(0.0f, 1.0f); glVertex3f(12.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(12.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(7.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(12.0f, -1.0f, -1.0f);  //������
	glTexCoord2f(1.0f, 1.0f); glVertex3f(12.0f, 3.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(12.0f, 3.0f, 3.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(12.0f, -1.0f, 3.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, -1.0f, -1.0f);  //������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(7.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(7.0f, 3.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(7.0f, 3.0f, -1.0f);
	glEnd();

}
void MyStripeImage() { // ������ ���ε� �ؽ��� �����Լ� (���簢���� �����츦 �θ�)                            
	for (int j = 0; j < stripeImageWidth; j++) {
		stripeImage[4 * j] = 255;
		stripeImage[4 * j + 1] = (j < 8) ? 0 : 255;
		stripeImage[4 * j + 2] = (j < 8) ? 0 : 255;
		stripeImage[4 * j + 3] = 0;
	}
}
void MyInit2(void) {

	MyStripeImage(); // ���� �� �����
	glBindTexture(GL_TEXTURE_1D, MyTextureObject[0]); // �ؽ��� ��ü ����(MyTextureObject�� 0�� �迭)
	// �ؽ��ĸ޸𸮿� �ø���(�׸��̹Ƿ� 1D, �ؽ��ĵ����Ͱ� ����� ���� ���� ������ (= �迭�̸�))
	glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
	// �ؽ�����ǥ �ڵ�����(��ü��ǥ����)
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	// ������� ����
	glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);
	// �ؽ��� �Ķ���� ���
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // �����������
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // �������� ���
	// �ؽ��� ȯ�� ��� (��ü�� ����� �ؽ��Ļ��� ���ؼ� ���� �� ����- ����ȿ�� �����ϸ鼭 ������)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_TEXTURE_GEN_S); // �ؽ��� �ڵ����� Ȱ��ȭ
	glEnable(GL_TEXTURE_1D); // 1D �ؽ��� ���� Ȱ��ȭ
}

void MyTimer2(int Value) { // �������� �������� ���� Ÿ�̸�
	if (Case == false) // Case�� �ʱⰪ�� false�� �����Ͽ�, �׻� ���̳������� �Ͽ���
	{
		snow = snow + 0.05; // ������ ��ġ�� �Ʒ��� 0.05�� ������
		if (snow >= 3.5) // ������ �Ʒ��� ����������
			snow = 0; // ������ġ�� ���ư����� �Ͽ���
		glutPostRedisplay();
		glutTimerFunc(55, MyTimer2, 1); // ���������� Ÿ�̸��̺�Ʈ �߻������ֱ�
	}
	else
		glutPostRedisplay();

}
void MyKeyboard(unsigned char key, int x, int y) { // Ű���� ������ ���� ������ ���۰���
	switch (key) {
	case 'Z': // z or Z�� ������, Case���� �����Ͽ� ���� �����ų� ���� ���߰� �� �� ����
	case 'z': // �ʱⰪ�� false�� ���� �׻� ����������
		if (Case == false) { // ���� ������ �ִ»�Ȳ����
			Case = true; // �� ����
		}
		else if (Case == true) { // ���� ���� ��Ȳ����
			Case = false; // �ٽ� �� ������ �ϱ�
			glutTimerFunc(55, MyTimer2, 1); // ������ Ÿ�̸� ȣ��
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}
void MySpecial(int key, int x, int y) { // ����Ű ���� = ������ ���۰���
	switch (key) {
	case GLUT_KEY_UP: // ������Ű�� ������, �ΰ��� ������ �������
		Const -= 0.5;
		Const2 -= 0.5;
		if (Const <= 2.0 || Const2 <= 2.0) { // Ư������̻� ��������� ���� ���ϰ��Ͽ���(���� �Ѱ�ġ����)
			Const = 2.0;
			Const2 = 2.0;
		}
		break;
	case GLUT_KEY_DOWN: // �Ʒ�����Ű, �ΰ��� ���� ��� ��� ����
		Const += 0.5;
		Const2 += 0.5;
		break;
	default:
		break;
	}
	glutPostRedisplay(); // ���÷��� �̺�Ʈ ���� �߻���Ű��
}

void MyMainMenu(int entryID) { // �ָ޴�
	if (entryID == 1) // �� �׸� Ŭ���� Stop�� ����
		Stop = 1;
	else if (entryID == 2)
	{
		Stop = 3;
	}
	glutPostRedisplay(); // ���÷����ݹ� �����߻���Ű��
}
void MyInit(void) { // ���࿡ �ʿ��� �ʱⰪ�� ����

	glGenTextures(2, MyTextureObject); // �ؽ��İ�ü�� 2�� �����ϱ� ���ؼ� �غ�

	glutAddMenuEntry("Open the gift !", 1); // �޴��׸�÷��
	glutAddMenuEntry("Come back !", 2); //(�׸��� �̸�, �׸��� ���õɶ� �޴��ݹ��Լ����� ���޵Ǵ� ������)
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ������ ��ư Ŭ���� �޴��� ��

	glMatrixMode(GL_PROJECTION); // ������Ľ���
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 1.0); // ������ ������
	glEnable(GL_DEPTH_TEST); // ��������� �������� ����� �ϵ��� ����
	glEnable(GL_CULL_FACE); // �ĸ����Ÿ�� Ȱ��ȭ
	glCullFace(GL_BACK);

}

void MyDisplay(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ �ʱ�ȭ�ϸ鼭 ���̹��۵� �ʱ�ȭ(�������Ÿ� ����)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ������ȯ
	if (Stop == 1) // 1�� �޴� Ŭ����, ������ �̵��Ǹ鼭 �غ�� ������ ������
	{
		// Ʈ���� �������� ���� �̵�(������ �����ֱ� ����)
		gluLookAt(0.5 + 12.0, 0.5, 4.0, 0.0 + 12.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		// ������ 4���� �����Ͽ���
		glViewport(0, 0, Width / 2, Height / 2);
		MyDisplay2(); // �츮�� ����� ������ ���� ������ü ����

		glViewport(Width / 2, 0, Width / 2, Height / 2);
		MyDisplay2(); // �츮�� ����� ������ ���� ������ü ����

		glViewport(0, Height / 2, Width / 2, Height / 2);
		MyDisplay2();
		glViewport(Width / 2, Height / 2, Width / 2, Height / 2);
		MyDisplay2();

	}
	else if (Stop == 3) // 2�� �޴� Ŭ����, Ʈ���� �ִ� ��ġ�� ���ƿ�
	{
		gluLookAt(0.5, 0.5, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		// Ʈ���� ���ƿö�, 2D Ȱ��ȭ�� ������������ Ʈ���� 2D�̹����� ������
		glDisable(GL_TEXTURE_2D); // �ݵ�� �ʿ�
		glViewport(0, 0, Width, Height);

	}
	else if (Stop == 0) // �ʱ���½���
	{
		gluLookAt(0.5, 0.5, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	// ������ �ΰ��� ����Ͽ���
	glEnable(GL_LIGHT0); // 0�� ���� Ȱ��ȭ
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Const); // ������� ����� ����(����Ű ���� -> Const�� ����)
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); // 0�� ������ ��ġ
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white); // 0�������� ���ݻ籤�� ���� ������� ����(��ü���� ��Ϻο�)
	glLightfv(GL_LIGHT0, GL_SPECULAR, white); // 0�� ������ ���ݻ籤�� ���� ������� ����

	glEnable(GL_LIGHT1); // 1�� ���� Ȱ��ȭ
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white); // 1�������� ���ݻ籤�� ���� ������� ����(��ü���� ��Ϻο�)
	glLightfv(GL_LIGHT1, GL_SPECULAR, white); // 1�� ������ ���ݻ籤�� ���� ������� ����
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Const2);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);



	glPushMatrix();

	// ���׸��� (�� 16�� �׸�- ������ ���������� �����ֵ���)
	glPushMatrix();
	glTranslatef(2.0, 7.0 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 6.5 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, 5.8 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 4.5 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��4
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 5.2 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��5
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 3.7 - snow + 0.6, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��6
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 4.5 - snow + 0.8, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��7
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 3.4 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��8
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 5.0 - snow, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��9
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 3.2 - snow + 1.0, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��10
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0, 4.2 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��11
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 5.5 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��12
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 5.0 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��13
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.3, 5.9 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��14
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.9, 6.9 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��15
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 6.0 - snow + 0.3, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.15, 30, 30); // ��16
	glPopMatrix();
	// ���׸��� ��

	// Ʈ���� ���߱�(����� �Ŵ޾Ƴ��� ��)
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0); // ������ ���
	glLineWidth(1.0); // ������ ����
	glBegin(GL_LINES);
	glVertex3f(-0.4, 4.5, 1.5);
	glVertex3f(1.5, 3.8, 0.8);
	glEnd();
	glFlush();

	glBegin(GL_LINES);
	glVertex3f(1.5, 3.8, 0.8);
	glVertex3f(-2.1, 2.3, 3.0);
	glEnd();
	glFlush();

	glBegin(GL_LINES);
	glVertex3f(-2.1, 2.3, 3.0);
	glVertex3f(3.9, 1.7, 4.1);
	glEnd();
	glFlush();

	// ���׸���
	// ��ġ���� �� ��Ƽ� �ﰢ�� �ΰ��� ����� �׷� ��ó�� ���̰� �Ͽ���
	glColor3f(1.0, 1.0, 0.0); // �����
	glBegin(GL_POLYGON); // �ﰢ�� 1
	glVertex3f(0.6, 5.4, 0.0);
	glVertex3f(0.0, 6.26, 0.0);
	glVertex3f(-0.6, 5.4, 0.0);
	glEnd();
	glFlush();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON); // �ﰢ�� 2
	glVertex3f(0.6, 5.9, 0.0);
	glVertex3f(-0.6, 5.9, 0.0);
	glVertex3f(0.0, 5.2, 0.0);
	glEnd();
	glFlush();

	// ���� �����, ������ ����ȿ���� ������ �ȵǰ� �ϱ� ���ؼ� ��� �� �׸���, ���� Ȱ��ȭ
	glEnable(GL_LIGHTING);

	// ��ı׸���(�� 9���� ���)
	// Ʈ�� ���� ������ �Ŵ޷��ֵ��� ����
	// ��� ����� �ֺ��ݻ� �� ���ݻ翡 ���� ��ü���� �ٸ��� �����Ͽ���
	// SolidSphere �� ���׶� ����� ����� �������
	glPushMatrix();
	glTranslatef(0.0, 4.6, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown); // ��ü�� Ư�� ����(�ֺ��ݻ�� ���ݻ翡 ���� ��ü��)
	glMaterialfv(GL_FRONT, GL_SPECULAR, white); // ���ݻ籤��� ����
	glutSolidSphere(0.3, 30, 30); // ��� 1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, 4.4, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, 3.5, 2.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 3.1, 2.4);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 4
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.9, 2.7, 2.5);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 5
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 1.9, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 6
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 1.65, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 7
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.53, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 8
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 1.35, 3.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glScalef(1.0, 0.1, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidSphere(0.3, 30, 30); // ��� 9
	glPopMatrix();

	// ��ı׸��� ��
	// Ʈ���׸���- SolidCone���� Ʈ������ ����
	glPushMatrix();
	glTranslatef(0.0, 0.9, 0.0);
	glScalef(3.0, 3.0, 3.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green); // Ʈ������ �ʷϻ�
	glMaterialfv(GL_FRONT, GL_SPECULAR, green);
	glutSolidCone(1.1, 1.5, 30, 30); // Ʈ��
	glPopMatrix();

	// Ʈ�� ��ħ���� �׸���
	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	glScalef(1.0, 2.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brown);
	glutSolidCube(1.5); //����
	glPopMatrix();

	// �����׸���- SolidCube�� ���簢�� ������� �������
	// MyInit2()�� ���� 4���� ���� ��ü�� �칫�� ������
	// �ٸ� ������ ���� ������ �κ��� ����������(��������)
	glPushMatrix();
	glTranslatef(2.3, -1.2, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	MyInit2();
	glutSolidCube(1.0); //����1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.3, -1.2, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
	glutSolidCube(1.0);//����2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.3, -1.4, 2.5);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidCube(1.0);// ����3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.4, -1.4, 2.5);
	glScalef(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glutSolidCube(1.0);// ����4
	glPopMatrix();

	glDisable(GL_TEXTURE_1D); // �׸� ��ü�� �칫�̰� ������ �ؽ�������� �Ͼ�Ƿ� �װ��� �����ϱ� ���� ��Ȱ��ȭ
	glDisable(GL_LIGHTING); // �ʿ��� �κп��� ������ ���������� ���������� ��Ȱ��ȭ��Ŵ

	glPopMatrix();
	glutSwapBuffers();

}

void MyReshape(int w, int h) { // ������ ũ�⸦ �����ص� ��ü�� �ְ��������
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ������ ������ ��ü�� �������� ����
	GLfloat WidthFactor = (GLfloat)w / (GLfloat)500;
	GLfloat HeightFactor = (GLfloat)h / (GLfloat)500;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7 * WidthFactor, 7 * WidthFactor, -4 * HeightFactor, 7 * HeightFactor, -8, 8);
}

int main(int argc, char** argv) {

	Width = 500; // �������� ����(������ȯ����� ���� ������ ����)
	Height = 500; // �������� ����(������ȯ����� ���� ������ ����)
	glutInit(&argc, argv);
	// �������Ÿ� ���� Z���� ����غ�, �ڿ������� �ִϸ��̼� ȿ���� ���� ���߹��ۻ��
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Width, Height); // ������ ������
	glutInitWindowPosition(100, 100); // �������� ��ġ
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu); 
	// ��������, Ű���� �ν��� ���� �޴�����⸦ ���⿡ �ξ���
	glutCreateWindow("HW#8");
	glutDisplayFunc(MyDisplay); // �ݹ��Լ� ���
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(55, MyTimer2, 1); // ���������� ���� ������ ȿ���� ���� Ÿ�̸�
	MyInit(); // ���ü��Ǵ�, ��������, ������ ���� �⺻����
	glutMainLoop();
	return 0;
}