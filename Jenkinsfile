pipeline {
    agent any
    stages {
        stage('clone') {
            steps {
                checkout scm
            }
        } 
        stage('prepare_env_in')
        {
            parallel {
                stage('prepare Ubuntu 16.04') {
                    steps {
                        sh 'scenarist.py run prepare_env_in:dockerImage=\"ubuntu:16.04\"'
                    }
                }
                stage('prepare Astralinux 1.11.9') {
                    steps {
                        sh 'scenarist.py run prepare_env_in:dockerImage=\"sogimu/astralinux:1.11.9\"'
                    }
                }
            }
        }
        stage('build') {
            steps {
                sh 'scenarist.py run build_in:dockerImage=\"ubuntu:16.04\"'
            }

        }
        stage('unit_tests') {
            steps {
                sh 'scenarist.py run unit_tests_in:dockerImage=\"ubuntu:16.04\"'
            }

        }
        stage('make_package') {
            steps {
                sh 'scenarist.py run make_package_in:dockerImage=\"ubuntu:16.04\"'
            }

        }
    }
    post {
        always {
            archiveArtifacts artifacts: 'build/*.deb', fingerprint: true
            junit 'build/tests/unit-tests/unit_tests_results.xml'
        }
    }
}
