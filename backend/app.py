from flask import Flask, request, jsonify, send_from_directory
from pathlib import Path
import subprocess, sys

ROOT = Path(__file__).resolve().parents[1]
ENGINE = ROOT / 'cpp' / ('regex_engine.exe' if sys.platform.startswith('win') else 'regex_engine')
app = Flask(__name__, static_folder=str(ROOT / 'frontend'), static_url_path='')

def run_engine(args):
    if not ENGINE.exists():
        return {'ok': False, 'error': f'C++ engine not built. Expected: {ENGINE}'}
    try:
        p = subprocess.run([str(ENGINE), *args], capture_output=True, text=True, timeout=8)
        import json
        data = json.loads(p.stdout or '{}')
        return data
    except subprocess.TimeoutExpired:
        return {'ok': False, 'error': 'Compilation timed out.'}
    except Exception as e:
        return {'ok': False, 'error': str(e)}

@app.get('/')
def index(): return send_from_directory(ROOT / 'frontend', 'index.html')

@app.post('/api/compile')
def compile_regex():
    data = request.get_json(silent=True) or {}
    regex = str(data.get('regex', ''))
    if not regex: return jsonify({'ok': False, 'error': 'Please enter a regular expression.'}), 400
    return jsonify(run_engine([regex]))

@app.post('/api/match')
def match_route():
    data = request.get_json(silent=True) or {}
    regex, string = str(data.get('regex', '')), str(data.get('string', ''))
    if not regex: return jsonify({'ok': False, 'error': 'Compile a regular expression first.'}), 400
    return jsonify(run_engine([regex, '--match', string]))

@app.post('/api/batch-match')
def batch_match_route():
    data = request.get_json(silent=True) or {}
    regex = str(data.get('regex', ''))
    strings = data.get('strings', [])
    if not regex:
        return jsonify({'ok': False, 'error': 'Regular expression is required.'}), 400
    if not isinstance(strings, list):
        return jsonify({'ok': False, 'error': 'strings must be an array.'}), 400
    if len(strings) > 1024:
        return jsonify({'ok': False, 'error': 'Batch size cannot exceed 1024 strings.'}), 400
    results = []
    for value in strings:
        result = run_engine([regex, '--match', str(value)])
        if not result.get('ok'):
            return jsonify(result), 400
        results.append({'string': str(value), 'accepted': bool(result.get('accepted')), 'path': result.get('path', [])})
    return jsonify({'ok': True, 'results': results})

@app.get('/api/health')
def health(): return jsonify({'ok': ENGINE.exists(), 'engine': str(ENGINE)})

if __name__ == '__main__': app.run(host='127.0.0.1', port=5000, debug=True)
