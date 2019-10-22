import subprocess

encoding = 'utf-8'

def check(expr, result, rcode):
    out =  subprocess.run(expr, stdout = subprocess.PIPE, shell = True)
    if out.returncode == rcode and result == str(out.stdout, encoding):
        print('{} = {}; passed'.format(expr, result))
    else:
        print(out)
        print('error {0} != {1}, got {2}'.format(expr,result, str(out.stdout,encoding)))

check('./alloc', 'No input\n', 1)
check('./alloc 10000000000000000000000', 'Bad alloc\n', 1)
check('./alloc 10 alloc 100', 'Not alloc\n', 0)
check('./alloc 100 alloc 5', '1\n', 0)
check('./alloc 100 alloc 50 alloc 20 alloc 25 alloc 5', '1\n1\n1\n1\n', 0)
check('./alloc 100 alloc 50 alloc 20 alloc 25 alloc 6', '1\n1\n1\nNot alloc\n', 0)
check('./alloc 10 alloc 5 alloc 5 alloc 5 reset alloc 6', '1\n1\nNot alloc\n1\n', 0)