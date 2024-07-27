FROM nginx:stable-alpine
RUN apk add --update python3
COPY index.html /usr/share/nginx/html/index.html
COPY index.js /usr/share/nginx/html/index.js
COPY index.wasm /usr/share/nginx/html/index.wasm