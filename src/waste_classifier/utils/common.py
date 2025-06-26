import os
from box.exceptions import BoxValueError
import yaml
from waste_classifier import logger
import json
import joblib
from box import ConfigBox
from pathlib import Path
from typing import Any, Union, List
import base64


def read_yaml(path_to_yaml: Union[str, Path]) -> ConfigBox:
    """
    Reads a YAML file and returns a ConfigBox object.

    Args:
        path_to_yaml (Union[str, Path]): The path to the YAML file.

    Returns:
        ConfigBox: The parsed YAML content as a ConfigBox object.

    Raises:
        ValueError: If the YAML file is empty.
        RuntimeError: If an error occurs while reading the file.
    """
    path_to_yaml = Path(path_to_yaml)
    try:
        with path_to_yaml.open() as yaml_file:
            content = yaml.safe_load(yaml_file)
            if content is None:
                raise ValueError("YAML file is empty")
            logger.info(f"YAML file loaded successfully from: {path_to_yaml}")
            return ConfigBox(content)
    except BoxValueError:
        raise ValueError("YAML file is empty or invalid format")
    except Exception as e:
        raise RuntimeError(f"Error reading YAML file: {e}") from e


def create_directories(paths: List[Union[str, Path]], verbose: bool = True):
    """
    Create directories from a list of paths.

    Args:
        paths (List[Union[str, Path]]): A list of directory paths to create.
        verbose (bool, optional): If True, log directory creation. Defaults to True.
    """
    for path in paths:
        path = Path(path)
        path.mkdir(parents=True, exist_ok=True)
        if verbose:
            logger.info(f"Created directory at: {path}")


def save_json(path: Union[str, Path], data: dict):
    """
    Save a dictionary to a JSON file.

    Args:
        path (Union[str, Path]): The path where the JSON file will be saved.
        data (dict): The data to be saved in the JSON file.
    """
    path = Path(path)
    with path.open("w") as f:
        json.dump(data, f, indent=4)
    logger.info(f"JSON file saved at: {path}")


def load_json(path: Union[str, Path]) -> ConfigBox:
    """
    Load JSON data from a file and return as a ConfigBox object.

    Args:
        path (Union[str, Path]): The path to the JSON file.

    Returns:
        ConfigBox: The JSON data as a ConfigBox object.
    """
    path = Path(path)
    with path.open() as f:
        content = json.load(f)
    logger.info(f"JSON file loaded successfully from: {path}")
    return ConfigBox(content)


def save_bin(data: Any, path: Union[str, Path]):
    """
    Save data to a binary file using joblib.

    Args:
        data (Any): The data to save.
        path (Union[str, Path]): The path where the binary file will be saved.
    """
    path = Path(path)
    joblib.dump(value=data, filename=path)
    logger.info(f"Binary file saved at: {path}")


def load_bin(path: Union[str, Path]) -> Any:
    """
    Load binary data from a file.

    Args:
        path (Union[str, Path]): The path to the binary file.

    Returns:
        Any: The object stored in the binary file.
    """
    path = Path(path)
    data = joblib.load(path)
    logger.info(f"Binary file loaded from: {path}")
    return data


def get_size(path: Union[str, Path]) -> str:
    """
    Get the size of a file in kilobytes.

    Args:
        path (Union[str, Path]): The path to the file.

    Returns:
        str: The size of the file in kilobytes (approximate).
    """
    path = Path(path)
    size_in_kb = round(path.stat().st_size / 1024)
    return f"~ {size_in_kb} KB"


def decode_image(img_string: str, file_name: Union[str, Path]):
    """
    Decode a base64 image string and save it to a file.

    Args:
        img_string (str): The base64-encoded image string.
        file_name (Union[str, Path]): The file path where the decoded image will be saved.
    """
    file_name = Path(file_name)
    img_data = base64.b64decode(img_string)
    with file_name.open('wb') as f:
        f.write(img_data)
    logger.info(f"Image decoded and saved at: {file_name}")


def encode_image_to_base64(image_path: Union[str, Path]) -> str:
    """
    Encode an image file to a base64 string.

    Args:
        image_path (Union[str, Path]): The path to the image file.

    Returns:
        str: The base64-encoded string of the image.
    """
    image_path = Path(image_path)
    with image_path.open("rb") as f:
        encoded_string = base64.b64encode(f.read()).decode('utf-8')
    logger.info(f"Image at {image_path} encoded to base64 string")
    return encoded_string
