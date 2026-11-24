'use strict';

// Zero-dependency HTTP server for the mini_infer solution download.
// Routes:
//   GET /                       download page with a button
//   GET /download/solution.zip  streams solution.zip as an attachment
//   GET /api/downloads          JSON manifest of available downloads
//   GET /health                 simple health check

const http = require('http');
const fs = require('fs');
const path = require('path');

const PORT = Number(process.env.PORT || 8000);
const ROOT = process.env.MINI_INFER_DIR || path.resolve(__dirname, '..');
const ZIP_PATH = path.join(ROOT, 'solution.zip');
const INDEX_PATH = path.join(__dirname, 'index.html');
const ZIP_NAME = 'mini-infer-solution.zip';

function send(res, status, body, headers = {}) {
  res.writeHead(status, { 'Content-Type': 'text/plain; charset=utf-8', ...headers });
  res.end(body);
}

function sendTextFile(res, file) {
  fs.readFile(file, (err, data) => {
    if (err) {
      send(res, 500, 'error: cannot read ' + path.basename(file) + '\n');
      return;
    }
    res.writeHead(200, {
      'Content-Type': 'text/html; charset=utf-8',
      'Content-Length': data.length,
    });
    res.end(data);
  });
}

function sendZip(res) {
  fs.stat(ZIP_PATH, (err, stat) => {
    if (err || !stat.isFile()) {
      send(res, 503,
        'error: solution.zip is missing. Run ./scripts/package-solution.sh first.\n');
      return;
    }
    res.writeHead(200, {
      'Content-Type': 'application/zip',
      'Content-Disposition': 'attachment; filename="' + ZIP_NAME + '"',
      'Content-Length': stat.size,
    });
    const stream = fs.createReadStream(ZIP_PATH);
    stream.on('error', () => {
      if (!res.headersSent) {
        send(res, 500, 'error: failed to read solution.zip\n');
      } else {
        res.destroy();
      }
    });
    stream.pipe(res);
  });
}

const routes = {
  'GET /': (_req, res) => sendTextFile(res, INDEX_PATH),
  'GET /health': (_req, res) => send(res, 200, JSON.stringify({ status: 'ok' }) + '\n',
    { 'Content-Type': 'application/json; charset=utf-8' }),
  'GET /api/downloads': (_req, res) => {
    fs.stat(ZIP_PATH, (err, stat) => {
      const body = {
        downloads: [{
          name: ZIP_NAME,
          path: '/download/solution.zip',
          size: err ? null : stat.size,
          available: !err && stat.isFile(),
        }],
      };
      send(res, 200, JSON.stringify(body) + '\n',
        { 'Content-Type': 'application/json; charset=utf-8' });
    });
  },
  'GET /download/solution.zip': (_req, res) => sendZip(res),
};

function router(req, res) {
  let pathname;
  try {
    pathname = new URL(req.url, 'http://localhost').pathname;
  } catch (_) {
    send(res, 400, 'error: bad request\n');
    return;
  }

  const handler = routes[req.method + ' ' + pathname];
  if (handler) {
    console.log(req.method + ' ' + pathname + ' 200');
    handler(req, res);
    return;
  }

  const pathExists = Object.keys(routes).some((key) => key.endsWith(' ' + pathname));
  if (pathExists) {
    console.log(req.method + ' ' + pathname + ' 405');
    send(res, 405, 'error: method not allowed\n', { Allow: 'GET' });
    return;
  }

  console.log(req.method + ' ' + pathname + ' 404');
  send(res, 404, 'error: not found\n');
}

const server = http.createServer(router);
server.listen(PORT, '0.0.0.0', () => {
  console.log('mini_infer download server listening on http://0.0.0.0:' + PORT);
  console.log('download page: http://localhost:' + PORT + '/');
  console.log('zip endpoint:  http://localhost:' + PORT + '/download/solution.zip');
});
