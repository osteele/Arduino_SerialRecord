#!/usr/bin/env bash

set -e

S3_BUCKET=assets.osteele.com
S3_DIR=arduino

name=SerialRecord
project_file=library.properties
zip_file=dist/${name}.zip

mkdir -p dist
rm -f "$zip_file"
zip -r "$zip_file" docs examples library.properties LICENSE* README* *.h

project_file_key=${S3_DIR}/${name}.txt
zip_key=${S3_DIR}/${name}.zip

aws s3 cp "$project_file" s3://${S3_BUCKET}/${project_file_key}
aws s3 cp "$zip_file" s3://${S3_BUCKET}/${zip_key}

aws s3api put-object-acl --bucket $S3_BUCKET --key $project_file_key --acl public-read
aws s3api put-object-acl --bucket $S3_BUCKET --key $zip_key --acl public-read
