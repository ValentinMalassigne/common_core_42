while ! mariadb -h${DB_HOST} -u${WP_DB_USER} -p${WP_DB_PASSWORD} ${WP_DB_NAME} &>/dev/null;
do
    sleep 1
done

if [ ! -f ${WP_PATH}/wp-config.php ]
then
	wp core download --allow-root
	wp config create --allow-root --dbname=${WP_DB_NAME} --dbuser=${WP_DB_USER} --dbpass=${WP_DB_PASSWORD} --dbhost=${DB_HOST} --path=${WP_PATH}
	wp core install --allow-root --url=${HOSTNAME}/wordpress --title=${WP_TITLE} --admin_user=${WP_ADMIN_USER} --admin_password=${WP_ADMIN_PASSWORD} --admin_email=${WP_ADMIN_EMAIL} --path=${WP_PATH}
	wp user create --allow-root ${WP_USER} ${WP_USER_EMAIL} --user_pass=${WP_USER_PASSWORD} --role=subscriber --display_name=${WP_USER} --porcelain --path=${WP_PATH}
	wp theme install blocksy --allow-root --path=${WP_PATH} --activate
fi

exec /usr/sbin/php-fpm81 -F -R
