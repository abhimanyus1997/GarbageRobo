import logging
from pathlib import Path
from tqdm.auto import tqdm
from colorama import Fore, Style, init

# Initialize colorama
init(autoreset=True)

# Configure logging
logging.basicConfig(level=logging.INFO, format='[%(asctime)s]: %(message)s')

# Project name
project_name = 'waste_classifier'

# List of required files and directories
list_of_files = [
    ".github/workflows/.gitkeep",
    f"src/{project_name}/__init__.py",
    f"src/{project_name}/components/__init__.py",
    f"src/{project_name}/utils/__init__.py",
    f"src/{project_name}/config/__init__.py",
    f"src/{project_name}/config/configuration.py",
    f"src/{project_name}/pipeline/__init__.py",
    f"src/{project_name}/entity/__init__.py",
    f"src/{project_name}/constants/__init__.py",
    "config/config.yaml",
    "dvc.yaml",
    "params.yaml",
    "requirements.txt",
    "setup.py",
    "research/trials.ipynb",
    "templates/index.html"
]

for filepath in tqdm(list_of_files, desc=f"{Fore.CYAN}Setting up project structure", colour='green'):
    file_path = Path(filepath)
    dir_path = file_path.parent

    # Create directories if they don't exist
    if not dir_path.exists() and str(dir_path) != ".":
        dir_path.mkdir(parents=True, exist_ok=True)
        logging.info(f"{Fore.YELLOW}Created directory: {dir_path}{Style.RESET_ALL}")

    # Create empty files if they don't exist or are empty
    if not file_path.exists() or file_path.stat().st_size == 0:
        file_path.touch()
        logging.info(f"{Fore.GREEN}Created empty file: {file_path}{Style.RESET_ALL}")
    else:
        logging.info(f"{Fore.BLUE}File already exists: {file_path}{Style.RESET_ALL}")
