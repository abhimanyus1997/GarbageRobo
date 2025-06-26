import setuptools

with open("README.md", "r", encoding="utf-8") as f:
    long_description = f.read()

__version__ = "0.0.0"

REPO_NAME = "waste-classifier-robot"
AUTHOR_USER_NAME = "abhimanyus1997"
SRC_REPO = "src"
AUTHOR_EMAIL = "abhimanyus1997@gmail.com"

setuptools.setup(
    name=REPO_NAME,
    version=__version__,
    author=AUTHOR_USER_NAME,
    author_email=AUTHOR_EMAIL,
    description="A deep learning solution for automated waste classification and robotic sorting.",
    long_description=long_description,
    long_description_content="text/markdown",
    url=f"https://github.com/{AUTHOR_USER_NAME}/{REPO_NAME}",
    project_urls={
        "Bug Tracker": f"https://github.com/{AUTHOR_USER_NAME}/{REPO_NAME}/issues",
    },
    # package_dir tells setuptools to look for packages in the 'src' directory
    # If your actual Python package is directly inside 'src/',
    # for example, 'src/waste_classifier/', then package_dir should be {'': 'src'}
    # and packages should be setuptools.find_packages(where="src").
    # If your root package is just 'src' itself, then `packages=['src']` or `setuptools.find_packages()` is fine.
    # Given your structure `src/`, let's assume `src` itself is the root package
    # Look for packages in the current directory (where setup.py is)
    package_dir={"": "."},
    # Find all packages starting from the current directory
    packages=setuptools.find_packages(where=".")
)
