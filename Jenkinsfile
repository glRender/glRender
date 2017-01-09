echo "Running ${env.BUILD_ID} on ${env.JENKINS_URL}"

stage('Checkout')
node
{
    checkout scm
    sh 'git submodule update --init --recursive'
}

stage('Build')
withEnv(["ENISEY_PATH=/opt/enisey"])
{
    node('master')
    {
        dir('build') {
            sh 'cmake ..'
            sh 'make'
        }
    }

    // node('astralinux1.11')
    // {
    //     dir('build') {
    //         sh 'cmake ..'
    //         sh 'make'
    //     }
    // }
}
