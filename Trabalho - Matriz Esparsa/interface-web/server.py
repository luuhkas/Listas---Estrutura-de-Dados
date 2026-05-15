from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import json
import subprocess


ROOT = Path(__file__).resolve().parent
PROJECT = ROOT.parent
BUILD = PROJECT / "build" / "trabalho_matriz_esparsa"


def compile_program():
    BUILD.parent.mkdir(exist_ok=True)
    command = [
        "clang",
        "-Wall",
        "-Wextra",
        str(PROJECT / "src" / "main.c"),
        str(PROJECT / "src" / "matriz_esparsa.c"),
        "-o",
        str(BUILD),
    ]
    subprocess.run(command, cwd=PROJECT, check=True, capture_output=True, text=True)


def run_program(input_text):
    sources = [
        PROJECT / "src" / "main.c",
        PROJECT / "src" / "matriz_esparsa.c",
        PROJECT / "src" / "matriz_esparsa.h",
    ]

    if not BUILD.exists() or any(source.stat().st_mtime > BUILD.stat().st_mtime for source in sources):
        compile_program()

    result = subprocess.run(
        [str(BUILD)],
        input=input_text,
        cwd=PROJECT,
        capture_output=True,
        text=True,
        timeout=5,
    )

    return result.stdout + result.stderr


class Handler(BaseHTTPRequestHandler):
    def send_common_headers(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_common_headers()
        self.end_headers()

    def do_GET(self):
        path = self.path.split("?", 1)[0]
        if path == "/":
            path = "/index.html"

        file_path = ROOT / path.lstrip("/")

        if not file_path.exists() or not file_path.is_file():
            self.send_error(404)
            return

        content_type = "text/plain"
        if file_path.suffix == ".html":
            content_type = "text/html"
        elif file_path.suffix == ".css":
            content_type = "text/css"
        elif file_path.suffix == ".js":
            content_type = "application/javascript"

        data = file_path.read_bytes()
        self.send_response(200)
        self.send_common_headers()
        self.send_header("Content-Type", f"{content_type}; charset=utf-8")
        self.send_header("Cache-Control", "no-store")
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def do_POST(self):
        if self.path != "/run":
            self.send_error(404)
            return

        length = int(self.headers.get("Content-Length", "0"))
        body = self.rfile.read(length)

        try:
            data = json.loads(body.decode("utf-8"))
            input_text = data["input"]
            output = run_program(input_text)
            response = {"ok": True, "output": output}
        except Exception as error:
            response = {"ok": False, "output": str(error)}

        payload = json.dumps(response).encode("utf-8")
        self.send_response(200)
        self.send_common_headers()
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(payload)))
        self.end_headers()
        self.wfile.write(payload)

    def log_message(self, format, *args):
        return


if __name__ == "__main__":
    server = ThreadingHTTPServer(("127.0.0.1", 8080), Handler)
    print("Interface web em http://127.0.0.1:8080")
    server.serve_forever()
