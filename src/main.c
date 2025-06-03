#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "decrypt.h"

static PyObject* run(PyObject* self, PyObject* args) {
    const char* encryptedCode;
    if (!PyArg_ParseTuple(args, "s", &encryptedCode)) {
        return NULL;
    }

    char* key = "Hello World!";

    const char* decrypted = decrypt(encryptedCode, key);

    PyObject* globals = PyDict_New();
    PyObject* locals = PyDict_New();

    PyObject* builtins = PyImport_ImportModule("builtins");
    if (!builtins) {
        PyErr_Print();
        Py_DECREF(globals);
        Py_DECREF(locals);
        return NULL;
    }
    PyObject* builtins_dict = PyModule_GetDict(builtins);
    PyDict_SetItemString(globals, "__builtins__", builtins_dict);
    Py_DECREF(builtins);

    PyObject* sysModule = PyImport_ImportModule("sys");
    if (sysModule) {
        PyDict_SetItemString(globals, "sys", sysModule);
        Py_DECREF(sysModule);
    }

    PyObject* compiled = Py_CompileString(decrypted, "<string>", Py_file_input);
    if (!compiled) {
        PyErr_Print();
        Py_DECREF(globals);
        Py_DECREF(locals);
        return NULL;
    }

    PyObject* result = PyEval_EvalCode(compiled, globals, globals);
    Py_DECREF(compiled);

    if (!result) {
        PyErr_Print();
        Py_DECREF(globals);
        Py_DECREF(locals);
        return NULL;
    }

    Py_DECREF(result);
    Py_DECREF(globals);
    Py_DECREF(locals);
    Py_RETURN_NONE;
}

static PyMethodDef Methods[] = {
    {"run", run, METH_VARARGS, "You've met a terrible fate. haven't you?"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ATFieldDRM = {
    PyModuleDef_HEAD_INIT,
    "ATFieldDRM",
    NULL,
    -1,
    Methods
};

PyMODINIT_FUNC PyInit_ATFieldDRM(void) {
    return PyModule_Create(&ATFieldDRM);
}