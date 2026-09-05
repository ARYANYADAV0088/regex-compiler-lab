import json, subprocess, sys
from pathlib import Path
ENGINE = Path(__file__).resolve().parents[1] / 'cpp' / ('regex_engine.exe' if sys.platform.startswith('win') else 'regex_engine')

def run(*args):
    p = subprocess.run([str(ENGINE), *args], text=True, capture_output=True)
    assert p.stdout, p.stderr
    return json.loads(p.stdout)

def main():
    cases = [
        ('a','a',True), ('a','b',False), ('abc','abc',True), ('abc','ab',False),
        ('a*b','aaab',True), ('a*b','aaa',False), ('a|b','b',True), ('a|b','c',False),
        ('(ab|ba)*','abba',True), ('(ab|ba)*','ababab',True),
        ('(a|b)*abb','aabb',True), ('(a|b)*abb','abab',False),
        ('a?','',True), ('a?','a',True), ('a+','aaaa',True), ('a+','',False),
        (r'\*','*',True),
    ]
    for regex, string, expected in cases:
        d = run(regex, '--match', string)
        assert d['accepted'] == expected, (regex, string, d)
        assert 'path' in d and 'steps' in d
    bad = ['(', 'a|', '*', 'a**', '|a', 'a(', ')', '\\']
    for regex in bad:
        d = run(regex)
        assert not d['ok'], (regex, d)
    # Structural checks on a representative compilation.
    d = run('(a|b)*abb')
    assert d['ok']
    assert d['stats']['nfaStates'] > 0
    assert d['stats']['dfaStates'] > 0
    assert d['stats']['minimizedStates'] > 0
    assert d['minimizationTrace']
    print(f'PASS: {len(cases)} matching cases + {len(bad)} invalid-regex cases + structural checks')

if __name__ == '__main__':
    main()
