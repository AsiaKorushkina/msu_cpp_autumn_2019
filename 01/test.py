import subprocess

encoding = 'utf-8'

def check(expr, result, rcode):
    out =  subprocess.run(expr, stdout = subprocess.PIPE, shell = True)
    if out.returncode == rcode and result == str(out.stdout, encoding):
        print('{} = {}; passed'.format(expr, result))
    else:
        print(out)
        print('error {0} != {1}, got {2}'.format(expr,result, str(out.stdout,encoding)))

check('./calc "23 + 26"', '49', 0)
check('./calc "2 + 2/2 + 3"', '6', 0)
check('./calc "-2 - - 2"', '0', 0)
check('./calc "2 -- 2"', '4', 0)
check('./calc "2  +3    "', '5', 0)
check('./calc "32* -1"', '-32', 0)
check('./calc "-1 * 2 + 100/20 - -1"', '4', 0)
check('./calc "1+23/0"', 'Division by zero', 2)
check('./calc', 'Invalid expression', 1)
check('./calc "2**/3"', 'Invalid expression', 1)
check('./calc "4 ++ 3"', 'Invalid expression', 1)
check('./calc "4 --- 4"', 'Invalid expression', 1)
check('./calc "32 + i"', 'Invalid expression', 1)
