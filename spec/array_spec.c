#include <assert.h>
#include <stdlib.h>
#include "cspec/array.h"
#include "cspec/cspec.h"

describe(array_new, "array_t* array_new(size_t element_size)")
    it("returns not-NULL pointer")
        array_t* array = array_new(1);
        should_not_be_null(array)
        array_delete(&array);
    end

    it("returns initialized struct")
        array_t* array = array_new(2);
        should_equal(array->element_size, 2)
        should_equal(array->size, 0)
        should_equal(array->capacity, 0)
        should_be_null(array->data)
        array_delete(&array);
    end

    it("returns NULL if element size is 0")
        should_be_null(array_new(0))
    end
end

describe(array_delete, "void array_delete(array_t** const array)")
    it("destruct struct")
        array_t* array = array_new(1);
        array->size = 1;
        array->capacity = 10;
        array->data = malloc(array->capacity);
        if (NULL == array->data) {
            exit(1);
        }
        array_delete(&array);
        should_be_null(array)
    end

    it("do nothing if pointer is NULL")
        array_delete(NULL);
        should_be_true(1)
    end

    it("do nothing if *array is NULL")
        array_t* array = NULL;
        array_delete(&array);
        should_be_null(array)
    end
end

describe(array_add, "int array_add(array_t* const array, const void* const data)")
    it("add an element into the array")
        int data;
        array_t* array;
        int ret;

        array = array_new(sizeof(int));
        assert(NULL != array);

        data = 2;
        ret = array_add(array, &data);
        should_equal(ret, 0)
        should_equal(array->size, 1)
        should_be_true(1 * sizeof(int) <= array->capacity)
        should_not_be_null(array->data)
        should_equal(*((int*) array_get_element(array, 0)), 2)
        should_be_null(array_get_element(array, 1))

        data = -1;
        ret = array_add(array, &data);
        should_equal(ret, 0)
        should_equal(array->size, 2)
        should_be_true(2 * sizeof(int) <= array->capacity)

        array_delete(&array);
    end

    it("returns 1 if either pointer is NULL")
        short data;
        array_t array;
        int ret = array_add(NULL, &data);
        should_equal(ret, 1)
        ret = array_add(&array, NULL);
        should_equal(ret, 1);
    end
end

describe(array_get_element, "void* array_get_element(array_t* const array, size_t idx)")
    it("return NULL if idx is over bound")
        array_t* array = array_new(sizeof(int));
        should_be_null(array_get_element(array, 1))
        array_delete(&array);
    end

    it("return NULL if pointer is NULL")
        should_be_null(array_get_element(NULL, 0))
    end
end
