# Create archives containing Yakforms packages.

# 1. Download latest version of Drupal.
mkdir ./yakforms_distribution
# TODO get latest version instead of hardcoded one, somehow
wget https://ftp.drupal.org/files/projects/drupal-7.80.zip
unzip ./drupal-7.80.zip
mv ./drupal-7.80/* ./yakforms_distribution

# 2. Create distribution (Drupal release + profile) archive
cp -r ./profiles/yakforms_profile ./yakforms_distribution/profiles
zip -r yakforms_distribution.zip ./yakforms_distribution
rm -rf yakforms_distribution drupal-7.80 drupal-7.80.zip

# 3. Create installation profile archive
zip -r ./yakforms_profile.zip profiles/yakforms_profile/*

# 4. TODO : FTP
