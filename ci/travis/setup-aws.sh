mkdir -p ~/.aws
cat > ~/.aws/credentials << EOL
[default]
aws_access_key_id = ${AWS_ACCESS_KEY_ID}
aws_secret_access_key = ${AWS_SECRET_ACCESS_KEY}
EOL

mkdir -p ${TRAVIS_BUILD_DIR}/package
aws s3 sync s3://${AWS_BUCKET}/package ${TRAVIS_BUILD_DIR}/package