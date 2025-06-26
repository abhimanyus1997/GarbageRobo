# Waste Classifier Robot

*An MLOps-driven solution for automated waste classification, enabling intelligent robotic sorting systems.*

## Table of Contents

- [Waste Classifier Robot](https://github.com/abhimanyus1997/waste-classifier-robot)
    - [Project Overview](#project-overview)
    - [Features](#features)
    - [Project Structure](#project-structure)
    - [Technology Stack](#technology-stack)
    - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
    - [Setting Up Environment Variables](#setting-up-environment-variables)
    - [Running the Project](#running-the-project)
    - [MLOps Workflow](#mlops-workflow)
    - [Contributing](#contributing)
    - [License](#license)
    - [Contact](#contact)


## Project Overview

The **Waste Classifier Robot** project delivers an intelligent system for accurate waste material classification, designed for seamless integration into robotic sorting processes. This end-to-end MLOps solution emphasizes reproducibility, scalability, and robust deployment, critical for industrial applications.

Key MLOps tenets integrated:

- **Data Version Control (DVC):** For disciplined management of data and model artifacts.
- **MLflow:** Centralized platform for experiment tracking, model lifecycle management, and deployment.
- **Reproducible Pipelines:** Leveraging `dvc.yaml` for deterministic model training and evaluation.
- **Modular Architecture:** Structured for maintainability and scalability in production environments.
- **API-driven Inference:** FastAPI provides a high-performance, well-documented interface for model predictions.

## Features

- **Automated Waste Classification:** High-accuracy classification of diverse waste categories.
- **End-to-End ML Pipeline:** Streamlined workflow from data ingestion to API deployment.
- **Comprehensive Experiment Tracking:** Detailed logging of training runs, metrics, and hyperparameters via MLflow.
- **Version-Controlled Assets:** DVC ensures traceability and reproducibility of all datasets and model versions.
- **Production-Ready API:** FastAPI and Uvicorn provide a robust, asynchronous inference endpoint.
- **CI/CD Integration:** `.github` workflows enable automated testing and deployment.

## Project Structure
The repository is structured for clarity and maintainability, supporting the full MLOps workflow:

```
.
├── .github/         # CI/CD workflows
├── config/          # Configuration files
├── research/        # Notebooks for EDA and prototyping
├── src/             # Core ML pipeline code
│   ├── components/  # Modular pipeline components
│   ├── pipelines/   # Workflow orchestration
│   ├── utils/       # Utilities and logging
├── templates/       # API/frontend templates
├── dvc.yaml         # DVC pipeline definition
├── main.py          # FastAPI app entry point
├── params.yaml      # Pipeline/model parameters
├── pyproject.toml   # Project metadata and dependencies
├── requirements.txt # Pip dependencies
├── setup.py         # Packaging config
└── uv.lock          # Dependency lock file
```

## Technology Stack

This project leverages a high-performance and industry-standard technology stack:

- **Python:** Primary development language.
- **PyTorch & torchvision:** Deep learning framework for computer vision.
- **pandas & NumPy:** Fundamental libraries for data manipulation and numerical operations.
- **Matplotlib & Seaborn:** For comprehensive data visualization and statistical plotting.
- **DVC:** For managing and versioning large datasets and ML models, ensuring pipeline reproducibility.
- **MLflow:** For end-to-end ML lifecycle management: tracking experiments, registering models, and deploying.
- **Jupyter Notebook:** For interactive development and exploratory analysis.
- **python-box & pyYAML:** For robust and human-readable configuration management.
- **tqdm:** For visualizing loop progress in long-running operations.
- **ensure:** For static and runtime type/value validation, enhancing code robustness.
- **joblib:** For efficient serialization of Python objects and parallel processing.
- **scipy:** For advanced scientific computing tasks.
- **FastAPI & Uvicorn:** For building and serving high-performance, asynchronous RESTful APIs.
- **gdown:** Utility for programmatic downloads from Google Drive.
- **uv:** Fast Python package installer and resolver, used for dependency management.

## Getting Started

Follow these steps to set up and run the project locally.

### Prerequisites

- Python 3.8+ (manage with `pyenv` for consistency)
- Git
- `uv` (install via `pip install uv`)

### Installation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/abhimanyus1997/waste-classifier-robot.git
    cd waste-classifier-robot
    ```

2. **Set up a virtual environment and install dependencies using `uv`:**

    ```bash
    uv venv       # Creates and activates a virtual environment
    uv sync       # Installs dependencies from pyproject.toml/uv.lock
    ```

    *(Note: `uv sync` will install dependencies and `uv` will also handle the equivalent of `pip install -e .` if configured in `pyproject.toml` or `setup.py`)*

### Setting Up Environment Variables

Create a `.env` file in the root directory for sensitive configurations.

```ini
# .env example
MLFLOW_TRACKING_URI=http://localhost:5000
# S3_BUCKET_NAME=your-mlops-data-bucket
# GCS_CREDENTIALS_PATH=/path/to/your/gcp-sa-key.json
```

### Running the Project

1. **Initialize DVC and configure remote storage:**

    ```bash
    dvc init --no-scm # If DVC will manage data independently of Git's tracking
    dvc remote add -d data_remote s3://your-s3-bucket/waste-classifier-robot-data # Example: Configure an S3 remote
    # Ensure your DVC remote is properly configured for data storage (S3, GCS, Azure, local shared drive, etc.)
    ```

2. **Pull versioned data (if applicable):**

    ```bash
    dvc pull
    ```

3. **Execute the ML pipeline (via DVC):**
    This command orchestrates the entire ML pipeline as defined in `dvc.yaml`, including data preprocessing, model training, and evaluation, with all runs tracked in MLflow.

    ```bash
    dvc repro
    ```

4. **Launch the MLflow UI:**
    To inspect experiment runs, compare metrics, and manage registered models:

    ```bash
    mlflow ui
    ```

    Access the UI in your browser at `http://localhost:5000`.

5. **Run the FastAPI inference service:**
    Serve the trained model as a high-performance REST API.

    ```bash
    uvicorn main:app --host 0.0.0.0 --port 8000 --reload
    ```

    Access the interactive API documentation (Swagger UI) at `http://localhost:8000/docs`.

## MLOps Workflow

This project adheres to a comprehensive MLOps workflow:

1. **Data Ingestion & Versioning:** Raw and processed data are versioned and managed using DVC, ensuring data lineage.
2. **Feature Engineering & Preprocessing:** Data transformations are defined and executed within reproducible DVC stages.
3. **Model Training & Experimentation:** Deep learning models are trained, with hyperparameters and performance metrics meticulously logged to MLflow Tracking.
4. **Model Evaluation & Validation:** Robust evaluation metrics are captured, facilitating rigorous model selection.
5. **Model Registry:** Best-performing models are registered in the MLflow Model Registry, providing a centralized, versioned repository.
6. **Model Deployment:** Registered models are deployed as scalable inference services using FastAPI and Uvicorn.
7. **Reproducibility:** `dvc.yaml` and `params.yaml` ensure that any experiment can be precisely reproduced, from data to model.
8. **Continuous Integration/Deployment (CI/CD):** `.github/workflows` automates testing, model building, and deployment, ensuring continuous delivery of ML capabilities.

## Contributing

Contributions are highly valued. Please refer to our `CONTRIBUTING.md` (to be created) for detailed guidelines on setting up your development environment, submitting pull requests, and coding standards.

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for full details.

---

### Attribution

This repository and its documentation were created by [Abhimanyu Singh](https://github.com/abhimanyus1997). If you use or adapt this project, please provide appropriate credit. Contributions and references to this work are welcome.

## Contact

For professional inquiries, collaborations, or technical support, please contact:

**Abhimanyu Singh**
[GitHub Profile](https://github.com/abhimanyus1997)
[LinkedIn Profile](https://www.linkedin.com/in/abhimanyus1997)
[Email](mailto:abhimanyus1997@gmail.com)