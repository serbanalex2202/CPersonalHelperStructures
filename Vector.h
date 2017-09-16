/*
 ============================================================================
 Name        : Vector.h
 Author      : Alexandru D Serban
 Version     : 1.0
 Copyright   : Personal Library
 Description : Vector Structure in C
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

#define PRINTNL printf("\n");

/*
 * Element contained by Vector
 */
typedef struct Element {
	char * str; /* Data */
	size_t dim; /* Memory needed */

} Element, *AElement;

void printEl(AElement e) {
	printf("%s\n", e->str);
}

void freeEl(AElement e) {
	free(e->str);
	free(e);
}

int compareEl(AElement e1, AElement e2) {
	return strcmp(e1->str, e2->str);
}

AElement cloneEl(AElement el) {
	AElement c = calloc(1, sizeof(Element));
	c->str = strdup(el->str);
	c->dim = el->dim;
	return c;

}

typedef struct Vector {

	AElement * vector;
	int size;
	int capacity;

	void (*addAtIndex)(struct Vector*, int, AElement);
	AElement (*showAtIndex)(struct Vector*, int);
	AElement (*popAtIndex)(struct Vector*, int);

	int (*binarySearch)(struct Vector*, AElement);
	int (*numberOfOcc)(struct Vector*, AElement);
	int (*indexOfFirstOcc)(struct Vector*, AElement);
	int (*indexOfLastOcc)(struct Vector*, AElement);

	void (*shrinkToSize)(struct Vector*);
	int (*isEmpty)(struct Vector*);
	int (*isEqual)(struct Vector*, struct Vector*);
	int (*containsAll)(struct Vector*, struct Vector*);
	int (*disjoint)(struct Vector*, struct Vector*);

	int (*replaceFirstOcc)(struct Vector*, AElement, AElement);
	int (*replaceLastOcc)(struct Vector*, AElement, AElement);
	int (*replaceAllOcc)(struct Vector*, AElement, AElement);
	void (*replaceAtIndex)(struct Vector*, int, AElement);

	void (*removeByIndex)(struct Vector*, int);
	int (*removeFirstOcc)(struct Vector*, AElement);
	int (*removeLastOcc)(struct Vector*, AElement);
	int (*removeAllOcc)(struct Vector*, AElement);
	int (*removeRange)(struct Vector*, int, int);
	int (*removeDups)(struct Vector*);

	void (*display)(struct Vector*);
	void (*sort)(struct Vector*);
	void (*reverse)(struct Vector*);
	void (*shuffle)(struct Vector*);
	void (*clear)(struct Vector*);
	void (*swap)(struct Vector*, int, int);

	struct Vector (*clone)(struct Vector*);

} Vector, *AVector;

Vector new_Vector();
void freeVector(AVector v);

/*
 * Doubles the capacity of the vector.
 */
void enlargeVector(AVector v) {

	int i;
	v->capacity *= 2;
	AElement * newv = (AElement *) calloc(v->capacity, sizeof(AElement *));
	for (i = 0; i < v->size; ++i) {
		newv[i] = v->vector[i];
	}
	free(v->vector);
	v->vector = newv;

}

/*
 * Reduces the capacity of the vector.
 */
void compressVector(AVector v) {

	int i;
	v->capacity /= 2;
	AElement * newv = (AElement *) calloc(v->capacity, sizeof(AElement *));
	for (i = 0; i < v->size; ++i) {
		newv[i] = v->vector[i];
	}
	free(v->vector);
	v->vector = newv;
}

/*
 * Shifts elements to the right and enlarges capacity if needed
 */
void shiftR(AVector v, int from) {
	int i;
	if (v->size == v->capacity) {
		enlargeVector(v);
	}

	for (i = v->size - 1; i >= from; --i) {
		v->vector[i + 1] = v->vector[i];
	}
	v->size++;
}

/*
 * Shifts elements to the left and reduces capacity if needed
 */
void shiftL(AVector v, int to) {

	int i;
	if (v->size <= v->capacity / 4) {
		compressVector(v);
	}

	for (i = to; i < v->size - 1; ++i) {
		v->vector[i] = v->vector[i + 1];
	}

	v->size--;
}

/*
 * Add given Element at specific index(allocates memory for it)
 */
void addAtIndex(AVector v, int i, AElement el) {

	if (i < 0 || i > v->size) {
		printf("addAtIndex : Invalid index\n");
		return;
	}

	/* Add last*/
	if (i == v->size) {
		if (v->size == v->capacity) {
			enlargeVector(v);
		}
		v->vector[i] = cloneEl(el);
		v->size++;
		return;
	}

	/* Add first*/
	if (i == 0) {
		shiftR(v, 0);
		v->vector[0] = cloneEl(el);
		return;
	}

	/* Add at Index*/
	shiftR(v, i);
	v->vector[i] = cloneEl(el);
	return;

}

/*
 * Returns but doesn't remove the element at given index.
 */
AElement showAtIndex(AVector v, int i) {
	if (i < 0 || i > v->size) {
		printf("showAtIndex : Invalid index, show first element\n");
		return v->vector[i];
	} else {
		return v->vector[i];
	}
}

/*
 * Returns and removes the element at given index.
 * The element returned must be freed later.
 */
AElement popAtIndex(AVector v, int i) {

	if (i < 0 || i > v->size) {
		printf("popAtIndex : Invalid index, pop first element\n");
		return v->vector[i];
	}
	/* If it is the last element*/
	if (i == v->size - 1) {
		v->size--;
		return v->vector[i];
	}

	AElement to_offer = v->vector[i];
	shiftL(v, i);
	return to_offer;

}

/*
 * Returns the index to first occurrence of given Element
 */
int indexOfFirstOcc(AVector v, AElement el) {
	int i;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(el, v->vector[i]) == 0) {
			return i;
		}
	}
	return -1;
}

int search(AVector v, AElement el, int left, int right) {

	if (right >= left && compareEl(v->vector[left], v->vector[right]) <= 0) {
		int mid = left + (right - left) / 2;

		if (compareEl(v->vector[mid], el) == 0) {
			return mid;
		}

		if (compareEl(el, v->vector[mid]) < 0) {/* If smaller search left*/

			printf("test\n");
			return search(v, el, left, mid - 1);

		}/* If bigger search right*/
		return search(v, el, mid + 1, right);

	}
	return -1;
}

/*
 *Binary Search for element O(log n) Complexity.
 *Returns index of element or -1 if element not found or if the vector is not sorted
 */
int binarySearch(AVector v, AElement el) {
	return search(v, el, 0, v->size - 1);
}

/*
 *Count occurrences of given element.
 */
int numberOfOcc(struct Vector* v, AElement el) {

	int i, count = 0;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(v->vector[i], el) == 0) {
			count++;
		}
	}

	return count;
}

/*
 * Returns the index to last occurrence of given Element
 */
int indexOfLastOcc(AVector v, AElement el) {
	int i;
	int found = -1;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(el, v->vector[i]) == 0) {
			found = i;
		}
	}
	return found;

}

/*
 * Reduces the capacity of the vector to its size
 */
void shrinkToSize(AVector v) {
	if (v->capacity == v->size) {
		return;
	}

	AElement * newv = calloc(v->size, sizeof(AElement*));
	v->capacity = v->size;
	memmove(newv, v->vector, v->size * sizeof(AElement));
	free(v->vector);
	v->vector = newv;
}

/*
 * Returns 1 if vector is Empty and 0 otherwise
 */
int isEmpty(AVector v) {
	return v->size == 0 ? 1 : 0;
}

/*
 * Returns 1 if vectors are equal and 0 otherwise
 */
int isEqual(AVector v1, AVector v2) {
	int i;

	if (v1->size != v2->size) {
		return 0;
	}

	for (i = 0; i < v1->size; ++i) {
		if (!(compareEl(v1->vector[i], v2->vector[i]))) {
			return 0;
		}
	}
	return 1;
}

/*
 * Returns 1 if vector1 contains all elements in vector 2 and 0 otherwise.
 * Search for every element in v2.
 * No duplicates detection.
 * If v2 contains 3 of e2 and v1 contains only 1 of v1 it will return true.
 */
int containsAll(AVector v1, AVector v2) {
	int i, j, found;
	for (i = 0; i < v2->size; ++i) {
		found = 0;
		for (j = 0; j < v1->size; ++j) {
			if (compareEl(v1->vector[j], v2->vector[i]) == 0) {
				found = 1;
				break;
			}
		}

		/* If we don't find current element*/
		if (found == 0) {
			return 0;
		}
	}

	return 1;
}

/*
 * Returns TRUE(1) if Vectors have nothing in common and FALSE(0) otherwise
 */
int disjoint(struct Vector* v1, struct Vector* v2) {
	int i, j;
	for (i = 0; i < v1->size; ++i) {
		for (j = 0; j < v2->size; ++j) {
			if (compareEl(v1->vector[i], v2->vector[j]) == 0) {
				return 0;
			}
		}
	}
	return 1;
}

/*
 * Returns 1 of given element was found and removed and 0 otherwise.
 * Replaces the first occurrence
 */
int replaceFirstOcc(AVector v, AElement el1, AElement el2) {
	int i;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(v->vector[i], el1) == 0) {
			freeEl(v->vector[i]);
			v->vector[i] = cloneEl(el2);
			return 1;
		}
	}
	return 0;
}

/*
 * Returns 1 of given element was found and removed and 0 otherwise.
 * Replaces the last occurrence
 */
int replaceLastOcc(AVector v, AElement el1, AElement el2) {
	int i, found = -1;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(v->vector[i], el1) == 0) {
			found = i;
		}
	}

	if (found != -1) {
		freeEl(v->vector[found]);
		v->vector[found] = cloneEl(el2);
		return 1;
	} else {
		return 0;
	}
}

/*
 * Replace all the elements equal to given element and returns the number of replaced elements.
 */
int replaceAllOcc(AVector v, AElement el1, AElement el2) {
	int i, count = 0;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(v->vector[i], el1) == 0) {
			freeEl(v->vector[i]);
			v->vector[i] = cloneEl(el2);
			count++;
		}
	}
	return count;

}

/*
 * Replace element at given index with given element and allocates memory for it
 */
void replaceAtIndex(AVector v, int i, AElement el) {
	freeEl(v->vector[i]);
	v->vector[i] = cloneEl(el);
}

/*
 * Remove element at given index
 */
void removeByIndex(AVector v, int i) {
	freeEl(v->vector[i]);
	shiftL(v, i);
}

/*
 * Remove first occurrence of given Element.
 * If element is found and removed returns 1 0 otherwise
 */
int removeFirstOcc(AVector v, AElement el) {

	int i;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(el, v->vector[i]) == 0) {
			freeEl(v->vector[i]);
			shiftL(v, i);
			return 1;
		}
	}
	return 0;
}

/*
 * Remove Last occurrence of given Element.
 * If element is found and removed returns 1 0 otherwise
 */
int removeLastOcc(AVector v, AElement el) {

	int i, to_rem = -1;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(el, v->vector[i]) == 0) {
			to_rem = i;
		}
	}

	if (to_rem != -1) {
		freeEl(v->vector[to_rem]);
		shiftL(v, to_rem);
		return 1;
	} else {
		return 0;
	}

}

/*
 * Remove all occurrences and returns the number of removed elements.
 */
int removeAllOcc(AVector v, AElement el) {
	int i, nr_rem = 0;
	for (i = 0; i < v->size; ++i) {
		if (compareEl(el, v->vector[i]) == 0) {
			freeEl(v->vector[i]);
			shiftL(v, i);
			nr_rem++;
			i--; /* Not to skip elements*/
		}
	}
	return nr_rem;
}

/*
 * Remove duplicates.
 * Returns number of removed elements.
 */
int removeRange(AVector v, int start, int end) {
	if (start > end || start > v->size - 1 || end > v->size - 1 || end < 0
			|| start < 0) {
		printf("removeGange : invalid range");
		return 0;
	}

	/* Remove elements from given interval
	 * for example
	 * [3 5];
	 * 0 1 2 _ _ _ 6 7  8  9  10 11 12 13 14
	 * 0 1 2 6 7 8 9 10 11 12 13 14 12 13 14
	 */
	int i, nr_rem = end - start + 1;
	for (i = 0; i < v->size; ++i) {
		if (i >= start && i <= end) {
			freeEl(v->vector[i]);
		}
	}

	v->size -= nr_rem;

	/* Shifts elements to the left nr_rem positions */
	for (i = start; i <= v->size; ++i) {
		v->vector[i] = v->vector[i + nr_rem];
	}

	if (v->size <= v->capacity / 4) {
		compressVector(v);
	}

	return nr_rem;
}

/*
 * Remove duplicates.
 */
int removeDups(AVector v) {
	int i, j, k = 0, nr_dups = 0, dup;

	AElement * newv = (AElement*) calloc(v->size, sizeof(AElement*));

	for (i = 0; i < v->size; ++i) {
		dup = 0;
		/* Start search from current element to end, so only the last occurrence of a duplicate will be copied*/
		for (j = i + 1; j < v->size; ++j) {
			if (compareEl(v->vector[i], v->vector[j]) == 0) {
				dup = 1; /* Mark duplicate found */
				freeEl(v->vector[i]);
				break; /* If duplicate found, break ,not to free same element again*/
			}
		}

		/* If ith element is not a duplicate*/
		if (dup == 0) {
			newv[k++] = v->vector[i];
		} else {
			nr_dups++;
		}
	}

	free(v->vector);
	v->vector = newv;
	v->size = k;
	if (v->size <= v->capacity / 4) {
		compressVector(v);
	}
	return nr_dups;
}

/*
 * Display Vector
 */
void display(AVector v) {

	if (v->size == 0) {
		printf("display : Vector size 0\n");
		return;
	}

	int i;

	for (i = 0; i < v->size; ++i) {
		printEl(v->vector[i]);
	}
}

/*
 * Merging elements in order in temporary array and then copy them to given array
 */
void merge(AVector v, int low, int mid, int high) {

	int i, m, k, l;
	AElement * temp = (AElement *) calloc(v->size, sizeof(AElement *));

	l = low;
	i = low;
	m = mid + 1;

	/* Compose new array choosing the smallest element from both halves*/
	while ((l <= mid) && (m <= high)) {

		if (compareEl(v->vector[l], v->vector[m]) <= 0) {
			temp[i] = v->vector[l];
			l++;
		} else {
			temp[i] = v->vector[m];
			m++;
		}
		i++;
	}

	if (l > mid) {/* Complete array with remaining elements from right half */
		for (k = m; k <= high; k++) {
			temp[i] = v->vector[k];
			i++;
		}
	} else {/* Complete array with remaining elements from left half */
		for (k = l; k <= mid; k++) {
			temp[i] = v->vector[k];
			i++;
		}
	}

	/* Copy ordered elements*/
	for (k = low; k <= high; k++) {
		v->vector[k] = temp[k];
	}

	free(temp);
}

/*
 * Divide Vector recursively in half.
 */
void part(AVector v, int lo, int hi) {

	if (lo < hi) {
		int m = (lo + hi) / 2;
		part(v, lo, m);
		part(v, m + 1, hi);
		merge(v, lo, m, hi);
	}

}

/*
 * Sort the vector using element comparator.
 * Merge sort.
 */
void sort(AVector v) {
	part(v, 0, v->size - 1);
}

/*
 * Reverse the Vector
 */
void reverse(AVector v) {
	int i;
	for (i = 0; i < v->size / 2; ++i) {
		AElement temp = v->vector[i];
		v->vector[i] = v->vector[v->size - i - 1];
		v->vector[v->size - i - 1] = temp;
	}
}

/*
 * Shuffle the vector elements.
 */
void shuffle(struct Vector* v) {

	struct timeval tv;
	int n = v->size;

	gettimeofday(&tv, NULL);
	int usec = tv.tv_usec;
	srand48(usec);

	if (n > 1) {
		int i;
		for (i = n - 1; i > 0; i--) {
			size_t j = (unsigned int) (drand48() * (i + 1));
			AElement t = v->vector[j];
			v->vector[j] = v->vector[i];
			v->vector[i] = t;
		}
	}
}

/*
 * Clear Vector :  free up memory, reduces size and capacity
 */
void clear(struct Vector* v) {
	freeVector(v);
	v->size = 0;
	v->capacity = 2;
	v->vector = (AElement *) calloc(2, sizeof(AElement *));
}

void swap(struct Vector* v, int poz1, int poz2) {

	if (poz1 < 0 || poz1 >= v->size || poz2 < 0 || poz2 >= v->size) {
		printf("swap : index out of range\n");
		return;
	}

	AElement temp;
	temp = v->vector[poz1];
	v->vector[poz1] = v->vector[poz2];
	v->vector[poz2] = temp;

}

/*
 * Returns a deep clone of given Vector
 */
Vector clone(AVector v) {
	int i;
	Vector c = new_Vector(v->size);
	c.size = v->size;
	for (i = 0; i < v->size; ++i) {
		c.vector[i] = cloneEl(v->vector[i]);
	}
	return c;
}

/**
 * Constructor Function
 */
Vector new_Vector(int init_cap) {

	Vector v;
	v.size = 0;
	v.capacity = init_cap;
	v.vector = (AElement *) calloc(init_cap, sizeof(AElement *));

	v.addAtIndex = &addAtIndex;
	v.showAtIndex = &showAtIndex;
	v.popAtIndex = &popAtIndex;

	v.binarySearch = &binarySearch;
	v.numberOfOcc = &numberOfOcc;
	v.indexOfFirstOcc = &indexOfFirstOcc;
	v.indexOfLastOcc = &indexOfLastOcc;

	v.shrinkToSize = &shrinkToSize;
	v.isEmpty = &isEmpty;
	v.isEqual = &isEqual;
	v.containsAll = &containsAll;
	v.disjoint = &disjoint;

	v.replaceFirstOcc = &replaceFirstOcc;
	v.replaceLastOcc = &replaceLastOcc;
	v.replaceAllOcc = &replaceAllOcc;
	v.replaceAtIndex = replaceAtIndex;

	v.removeByIndex = &removeByIndex;
	v.removeFirstOcc = &removeFirstOcc;
	v.removeLastOcc = &removeLastOcc;
	v.removeAllOcc = &removeAllOcc;
	v.removeRange = &removeRange;
	v.removeDups = &removeDups;

	v.display = &display;

	v.sort = &sort;
	v.reverse = &reverse;
	v.shuffle = &shuffle;
	v.clear = &clear;
	v.swap = &swap;

	v.clone = &clone;

	return v;
}

/*
 * Free given Vector
 */
void freeVector(AVector v) {

	int i;
	AElement e;

	/* Free each element */
	for (i = 0; i < v->size; ++i) {
		e = v->vector[i];
		freeEl(e);
	}

	/* Free vector*/
	free(v->vector);

}

/*
 * Free given number of Vectors
 */
void freeVectors(int nr_args, ...) {

	va_list valist;
	int i;
	AVector v;

	va_start(valist, nr_args);
	/*initialize list of Vectors*/

	for (i = 0; i < nr_args; i++) {

		v = va_arg(valist, AVector);
		freeVector(v);

	}

	va_end(valist);
}
