node {
    stage('clone') {
		checkout scm
	}	
    stage('build') {
        sh 'scenarist.py run default:dockerImage=\"ubuntu:16.04\"'
    }
}