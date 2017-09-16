#include "Vector.h"

int main() {

	char * s1 = "str1";
	char * s2 = "str2";
	char * s3 = "str3";
	char * s4 = "str4";
	char * s5 = "str5";
	char * s6 = "str6";
	char * s7 = "str7";
	char * s8 = "str8";
	char * s9 = "str9";

	Element e1, e2, e3, e4, e5, e6, e7, e8, e9;
	e1.str = s1;
	e1.dim = strlen(s1);

	e2.str = s2;
	e2.dim = strlen(s2);

	e3.str = s3;
	e3.dim = strlen(s3);

	e4.str = s4;
	e4.dim = strlen(s4);

	e5.str = s5;
	e5.dim = strlen(s5);

	e6.str = s6;
	e6.dim = strlen(s6);

	e7.str = s7;
	e7.dim = strlen(s7);

	e8.str = s8;
	e8.dim = strlen(s8);

	e9.str = s9;
	e9.dim = strlen(s9);

	Vector v1 = new_Vector(2);
	Vector v2 = new_Vector(3);
	Vector v3;
	Vector v4 = new_Vector(4);
	Vector v5 = new_Vector(2);

	/*****************************************************************/

	printf("------comp------\n");
	printf("comp : %d\n", compareEl(&e5, &e4));

	printf("------add Last------\n");
	v1.addAtIndex(&v1, v1.size, &e1);
	v1.addAtIndex(&v1, v1.size, &e2);
	v1.addAtIndex(&v1, v1.size, &e3);
	v1.addAtIndex(&v1, v1.size, &e4);
	v1.addAtIndex(&v1, v1.size, &e5);
	v1.addAtIndex(&v1, v1.size, &e6);
	v1.display(&v1);
	printf("cap: %d size: %d\n", v1.capacity, v1.size);

	printf("------add First si atIndex------\n");
	printf("cap: %d size: %d\n", v2.capacity, v2.size);
	v2.addAtIndex(&v2, 0, &e1);
	v2.addAtIndex(&v2, 0, &e2);
	v2.addAtIndex(&v2, 0, &e3);
	v2.addAtIndex(&v2, 2, &e6);
	v2.display(&v2);

	printf("------Clone------\n");
	v3 = v2.clone(&v2);
	printf("v\n");
	v3.display(&v3);
	v2.addAtIndex(&v2, 2, &e6);
	printf("v2 modificat \n");
	v2.display(&v2);
	printf("v\n");
	v3.display(&v3);

	printf("------reverse-----\n");
	v1.display(&v1);
	v1.reverse(&v1);
	printf("<->\n");
	v1.display(&v1);

	printf("------showAt Index-----\n");
	AElement temp = v1.showAtIndex(&v1, 2);
	printf("temp.str %s\n", temp->str);

	printf("------shiftR-----\n");
	v4.addAtIndex(&v4, v4.size, &e1);
	v4.addAtIndex(&v4, v4.size, &e2);
	v4.display(&v4);
	printf("cap: %d size: %d\n", v4.capacity, v4.size);
	v4.addAtIndex(&v4, v4.size, &e3);
	v4.addAtIndex(&v4, v4.size, &e4);
	v4.addAtIndex(&v4, v4.size, &e5);
	v4.addAtIndex(&v4, v4.size, &e6);
	v4.display(&v4);
	printf("cap: %d size: %d\n", v4.capacity, v4.size);

	printf("------POP AT INDEX-----\n");
	v3.display(&v3);
	temp = v3.popAtIndex(&v3, 2);
	printf("temp.str %s\n", temp->str);
	v3.display(&v3);
	freeEl(temp);

	printf("------replace AT INDEX-----\n");
	v3.replaceAtIndex(&v3, 2, &e3);
	v3.display(&v3);

	printf("------remove by INDEX-----\n");
	v3.removeByIndex(&v3, 2);
	v3.display(&v3);

	printf("------remove first OCCURRENCE-----\n");
	v3.addAtIndex(&v3, 2, &e1);
	v3.addAtIndex(&v3, 2, &e1);
	v3.addAtIndex(&v3, 2, &e1);
	v3.addAtIndex(&v3, 2, &e1);
	v3.addAtIndex(&v3, 0, &e1);
	v3.addAtIndex(&v3, 0, &e1);
	v3.addAtIndex(&v3, 0, &e1);
	v3.addAtIndex(&v3, 0, &e1);
	v3.addAtIndex(&v3, v3.size, &e1);
	v3.addAtIndex(&v3, v3.size, &e1);
	v3.display(&v3);
	v3.removeFirstOcc(&v3, &e1);
	printf("---\n");
	v3.display(&v3);

	printf("------remove last OCCURRENCE-----\n");
	v3.removeLastOcc(&v3, &e1);
	v3.display(&v3);

	printf("------remove all OCCURRENCEs-----\n");
	printf("cap: %d size: %d\n", v3.capacity, v3.size);
	v3.removeAllOcc(&v3, &e1);
	v3.display(&v3);
	printf("cap: %d size: %d\n", v3.capacity, v3.size);

	printf("------sort-----\n");
	v3.addAtIndex(&v3, 0, &e6);
	v3.addAtIndex(&v3, 0, &e5);
	v3.addAtIndex(&v3, 0, &e1);
	v3.addAtIndex(&v3, 0, &e2);
	v3.addAtIndex(&v3, 0, &e6);
	v3.display(&v3);
	printf("-----\n");
	v3.sort(&v3);
	v3.display(&v3);

	/**************************TO TEST***************************/

	printf("------shrink To Size-----\n");
	printf("cap: %d size: %d\n", v5.capacity, v5.size);
	v5.addAtIndex(&v5, 0, &e6);
	v5.addAtIndex(&v5, 0, &e6);
	v5.addAtIndex(&v5, 0, &e6);
	printf("cap: %d size: %d\n", v5.capacity, v5.size);
	v5.shrinkToSize(&v5);
	v5.display(&v5);
	printf("cap: %d size: %d\n", v5.capacity, v5.size);

	printf("------index First Last Occ-----\n");
	v5.addAtIndex(&v5, 0, &e1);
	v5.addAtIndex(&v5, v5.size, &e1);
	v5.display(&v5);
	printf("%d\n", v5.indexOfFirstOcc(&v5, &e6));
	printf("%d\n", v5.indexOfLastOcc(&v5, &e6));

	printf("------containsAll-----\n");
	v4.display(&v4);
	printf("------\n");
	v5.display(&v5);
	printf("contains %d\n", v5.containsAll(&v4, &v5));

	printf("------replace first last All-----\n");
	v5.addAtIndex(&v5, 3, &e1);
	v5.addAtIndex(&v5, 3, &e1);
	v5.addAtIndex(&v5, 3, &e1);
	v5.addAtIndex(&v5, 3, &e1);
	printf("------\n");
	v5.display(&v5);
	v5.replaceFirstOcc(&v5, &e1, &e2);
	v5.replaceFirstOcc(&v5, &e1, &e2);
	printf("------\n");
	v5.display(&v5);
	v5.replaceLastOcc(&v5, &e1, &e2);
	printf("------\n");
	v5.display(&v5);
	v5.replaceAllOcc(&v5, &e1, &e2);
	printf("------\n");
	v5.display(&v5);

	printf("------remove range-------\n");
	printf("cap: %d size: %d\n", v5.capacity, v5.size);
	v5.removeRange(&v5, 3, 8);
	v5.display(&v5);
	printf("cap: %d size: %d\n", v5.capacity, v5.size);

	printf("------remove Dups-------\n");
	v5.addAtIndex(&v5, 0, &e1);
	v5.addAtIndex(&v5, 0, &e2);
	v5.addAtIndex(&v5, 0, &e3);
	v5.addAtIndex(&v5, 0, &e1);
	v5.addAtIndex(&v5, 2, &e4);
	v5.addAtIndex(&v5, 3, &e4);
	v5.display(&v5);
	printf("cap: %d size: %d\n", v5.capacity, v5.size);

	printf("nr dups : %d\n", v5.removeDups(&v5));
	printf("---\n");
	v5.display(&v5);
	printf("cap: %d size: %d\n", v5.capacity, v5.size);

	printf("------clear-------\n");
	v4.clear(&v4);
	v4.display(&v4);

	printf("------disjoint-------\n");
	v4.addAtIndex(&v4, 0, &e6);
	v4.addAtIndex(&v4, 0, &e6);
	v4.addAtIndex(&v4, 0, &e6);
	v4.display(&v4);
	printf("---\n");
	v5.removeAllOcc(&v5, &e6);
	v5.display(&v5);
	printf("disjoint : %d\n", v4.disjoint(&v4, &v5));

	printf("------binary search------\n");
	v4.clear(&v4);
	v4.addAtIndex(&v4, 0, &e1);
	v4.addAtIndex(&v4, 0, &e2);
	v4.addAtIndex(&v4, 0, &e3);
	v4.addAtIndex(&v4, 0, &e3);
	v4.addAtIndex(&v4, 0, &e3);
	v4.addAtIndex(&v4, 0, &e3);
	v4.addAtIndex(&v4, 0, &e3);
	v4.addAtIndex(&v4, 0, &e4);
	v4.addAtIndex(&v4, 0, &e5);
	v4.addAtIndex(&v4, 0, &e6);
	v4.addAtIndex(&v4, 0, &e7);
	v4.addAtIndex(&v4, 0, &e7);
	v4.addAtIndex(&v4, 0, &e7);
	v4.addAtIndex(&v4, 0, &e7);
	v4.addAtIndex(&v4, 0, &e8);
	v4.addAtIndex(&v4, 0, &e9);
	v4.addAtIndex(&v4, 0, &e9);
	v4.addAtIndex(&v4, 0, &e9);
	v4.addAtIndex(&v4, 0, &e9);
	v4.addAtIndex(&v4, 0, &e9);
	v4.addAtIndex(&v4, 0, &e9);
	v4.reverse(&v4);
	v4.display(&v4);
	printf("index : %d\n", v4.binarySearch(&v4, &e8));

	printf("------count------\n");
	v4.clear(&v4);
	v4.addAtIndex(&v4, 0, &e1);
	v4.addAtIndex(&v4, 0, &e5);
	v4.addAtIndex(&v4, 0, &e2);
	v4.addAtIndex(&v4, 0, &e5);
	v4.addAtIndex(&v4, 0, &e3);
	v4.addAtIndex(&v4, 0, &e5);
	v4.addAtIndex(&v4, 0, &e4);
	v4.addAtIndex(&v4, 0, &e5);
	printf("cound : %d\n", v4.numberOfOcc(&v4, &e5));

	printf("------shuffle------\n");
	v4.display(&v4);
	PRINTNL v4
	.shuffle(&v4);
	v4.display(&v4);

	printf("========free=======\n");
	freeVectors(5, &v1, &v2, &v3, &v4, &v5);

	return 0;

}
